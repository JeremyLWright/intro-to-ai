/**
 * @brief CSE 471 Homework 15
 *
 * @par
 * Copyright Jeremy Wright (c) 2013
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */

#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <boost/filesystem.hpp>
#include <boost/assert.hpp>
#include <gnuplot-iostream/gnuplot-iostream.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "prettyprint.hpp"
  using std::cout;
  using std::endl;
  using std::boolalpha;
#include <map>
  using std::map;
#include <cmath>
  using std::sqrt;
#include <string>
  using std::string;

#include <boost/regex.hpp>

enum Bag {
    Bag1 =1,
    Bag2,
    Bag3,
    Bag4,
    Bag5};

std::vector<Bag> const bags{Bag1, Bag2, Bag3, Bag4, Bag5};

map<Bag, double> apriori{
        {Bag1, 0.1},
        {Bag2, 0.2},
        {Bag3, 0.4},
        {Bag4, 0.2},
        {Bag5, 0.1}
};

map<Bag, std::pair<double, double>> candy_dist{
        {Bag1, {1.00, 0.00}},
        {Bag2, {0.75, 0.25}},
        {Bag3, {0.50, 0.50}},
        {Bag4, {0.25, 0.75}},
        {Bag5, {0.00, 1.00}}
};

class lime_type{};
class cherry_type{};
class data_type{};

size_t num_limes = 0;
size_t num_cherries = 0;

void process(lime_type)
{
    ++num_limes;
}

void process(cherry_type)
{
    ++num_cherries;
}
double p(lime_type, Bag bag)
{
    double d = candy_dist.at(bag).second;
    //cout << "P(lime|Bag"<< bag << ")=" << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}

double p(cherry_type, Bag bag)
{
    double d = candy_dist.at(bag).first;
    //cout << "P(cherry|Bag" << bag << ")=" << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}

double p(Bag bag)
{
    double d = apriori.at(bag); 
  //  cout << "P(bag"<< bag << ")=" << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}

double p(data_type, Bag bag)
{
    double d = pow(p(lime_type(), bag), num_limes) * pow(p(cherry_type(), bag), num_cherries);
//    cout << "P(data|bag"<< bag << ")=" << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}

double p(data_type)
{
    // p(data) = \Sigma_B ( p(data | B_i) * p(B_i)
    std::vector<double> partials(bags.size());
    std::transform(begin(bags), end(bags), begin(partials), [](Bag b){ return  p(data_type(), b) * p(b); });

    double d = std::accumulate(begin(partials), end(partials), 0.0 );
    
    //cout << "P(data) " << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;

}


double p(Bag bag, data_type)
{
    // p(bag_i | Data) => p(data | bag_i)*p(bag_i)/p(data)
    double d = (p(data_type(), bag) * p(bag)) / p(data_type());
    //cout << "P(bag" << bag << "|data) " << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}

// Calculates the probabilty the next candy will be a lime.
double p(lime_type, data_type)
{
    // 
    // \sigma_bags(p(lime, Bag_i | data))
    //
    std::vector<double> partials(bags.size());
    std::transform(begin(bags), end(bags), begin(partials), [](Bag b){ return  p(lime_type(), b)*p(b, data_type()); });
    double a = std::accumulate(begin(partials), end(partials), 0.0 );
    BOOST_VERIFY( a >= 0 && a <= 1 );
    return a;

    /*
    p(lime_type(), Bag2)*p(Bag2, data_type()) +
    p(lime_type(), Bag3)*p(Bag3, data_type()) +
    p(lime_type(), Bag4)*p(Bag4, data_type()) +
    p(lime_type(), Bag5)*p(Bag5, data_type());
    */

        
}

double p(cherry_type, data_type)
{
    // 
    // \sigma_bags(p(lime, Bag_i | data))
    //
    std::vector<double> partials(bags.size());
    std::transform(begin(bags), end(bags), begin(partials), [](Bag b){ return  p(cherry_type(), b)*p(b, data_type()); });
    double a = std::accumulate(begin(partials), end(partials), 0.0 );
    BOOST_VERIFY( a >= 0 && a <= 1 );
    return a;

    /*
    p(lime_type(), Bag2)*p(Bag2, data_type()) +
    p(lime_type(), Bag3)*p(Bag3, data_type()) +
    p(lime_type(), Bag4)*p(Bag4, data_type()) +
    p(lime_type(), Bag5)*p(Bag5, data_type());
    */

        
}


using dataset_t = std::vector<std::pair<double, double>>;
using datasets_t = std::vector<std::pair<string, dataset_t>>;

void plot(datasets_t datasets, string filename)
{
    Gnuplot gp;
	
    std::vector<string> plot_commands;
    size_t max_set{0};
    for(auto dataset : datasets)
    {
        std::stringstream ss;
        ss << "'-' with lines title '"<< dataset.first << "'";
        plot_commands.push_back(ss.str());
        max_set = dataset.second.size() > max_set ? dataset.second.size() : max_set;
    }
   
    //Make comma separated.
    std::stringstream ss;
    for (auto i = plot_commands.begin(); i != plot_commands.end(); ++i) 
    {
        if (i != plot_commands.begin()) ss << ", ";
        ss << *i;
    }
	
    gp << "set term png\n"; 
    gp << "set output '"<< filename << ".png'\n";
	gp << "set xrange [0:" << max_set << "]\nset yrange [0:1]\n";
    gp << "plot ";
    gp << ss.str();
    gp << '\n';
    
    //gp << ",'-' with lines title '"<< filename << "2'\n";
    for(auto points : datasets)
        gp.send1d(points.second);
    gp << '\n';

    //gp.send1d(dataset2);
}


int main(int argc, char* argv[])
{
    std::string appName = boost::filesystem::basename(argv[0]); 
    po::options_description desc("Options");

    std::string filename;
    desc.add_options()
        ("help,h", "This program accepts the name of a file.")
        ("file,f", po::value<std::string>(), "new line delimited file.");
    try
    {
        po::positional_options_description p;
        p.add("file", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        if(vm.count("file"))
        {
            filename = vm["file"].as<std::string>();
        }
        else
        {
            std::cout << desc << endl;
            return 0;
        }

    }
    catch(boost::program_options::required_option& e) 
    { 
        std::cout << desc << endl;
    } 

    std::ifstream fin(filename);
    string line;
    boost::regex reg("c|l"); //Construct the regular expression here, since it's expensive
    size_t lineno{0};

    while(std::getline(fin,line))
    {
        ++lineno;
        string candy;
        num_limes = 0;
        num_cherries = 0;
        boost::sregex_token_iterator pos(begin(line), end(line), reg);
        boost::sregex_token_iterator end;

        dataset_t h1;
        dataset_t h2;
        dataset_t h3;
        dataset_t h4;
        dataset_t h5;
        dataset_t plime;
        dataset_t pcherry;
        for(size_t sample = 0 ; pos != end ; ++pos, ++sample)
        {
            if(pos->str() == "l")
                process(lime_type());
            if(pos->str() == "c")
                process(cherry_type());

            std::vector<double> prob(bags.size());
            std::transform(std::begin(bags), std::end(bags), begin(prob), [](Bag b){ return  p(b, data_type()); });
            //cout << "Sample: " << sample << ": " << prob[1] << '\n';
            h1.push_back(std::make_pair(sample, prob[0]));
            h2.push_back(std::make_pair(sample, prob[1]));
            h3.push_back(std::make_pair(sample, prob[2]));
            h4.push_back(std::make_pair(sample, prob[3]));
            h5.push_back(std::make_pair(sample, prob[4]));
            plime.push_back(std::make_pair(sample, p(lime_type(), data_type())));
            pcherry.push_back(std::make_pair(sample, p(cherry_type(), data_type())));

            //cout << "{";
            //std::copy(std::begin(prob), std::end(prob), std::ostream_iterator<double>(cout, ", "));
            //cout << "}" << endl;
        }
        //for(auto& p : h2)
        //{
        //    cout << p.first << " : " << p.second << endl;
        //}
        //cout << endl;
        datasets_t d{
        std::make_pair("P(Bag1 | D)", h1),
        std::make_pair("P(Bag2 | D)", h2), 
        std::make_pair("P(Bag3 | D)", h3), 
        std::make_pair("P(Bag4 | D)", h4), 
        std::make_pair("P(Bag5 | D)", h5),
        std::make_pair("P(lime | D)", plime),
        std::make_pair("P(cherry | D)", pcherry)};

        //plot(h1, string("H1_Line_")+std::to_string(lineno));
        plot(d, string("Line")+std::to_string(lineno));
        //plot(h3, string("H3_Line_")+std::to_string(lineno));
        //plot(h4, string("H4_Line_")+std::to_string(lineno));
        //plot(h5, string("H5_Line_")+std::to_string(lineno));
        //cout << endl;

    }

    return 0;
}
