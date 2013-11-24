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


using dataset_t = std::vector<std::pair<double, double>>;

void plot(dataset_t dataset, string filename)
{
    Gnuplot gp;
    
    
   	std::vector<std::pair<double, double> > xy_pts_B;
	for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
		double theta = alpha*2.0*3.14159;
		xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
	}

	std::cout << "Creating my_graph_2.png" << std::endl;
	gp << "set output '"<< filename << ".png'\n";
	gp << "set xrange [-2:12]\nset yrange [0:1]\n";
    gp << "plot '-' with lines title '"<< filename << "'\n";

    gp.send1d(dataset);
}

void demo_png() {
	Gnuplot gp;

	gp << "set terminal png\n";

	std::vector<double> y_pts;
	for(int i=0; i<1000; i++) {
		double y = (i/500.0-1) * (i/500.0-1);
		y_pts.push_back(y);
	}

	std::cout << "Creating my_graph_1.png" << std::endl;
	gp << "set output 'my_graph_1.png'\n";
	gp << "plot '-' with lines, sin(x/200) with lines\n";
	gp.send1d(y_pts);

	std::vector<std::pair<double, double> > xy_pts_A;
	for(double x=-2; x<2; x+=0.01) {
		double y = x*x*x;
		xy_pts_A.push_back(std::make_pair(x, y));
	}

	std::vector<std::pair<double, double> > xy_pts_B;
	for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
		double theta = alpha*2.0*3.14159;
		xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
	}

	std::cout << "Creating my_graph_2.png" << std::endl;
	gp << "set output 'my_graph_2.png'\n";
	gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
    gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";

    gp.send1d(xy_pts_A);
    gp.send1d(xy_pts_B);
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

            //cout << "{";
            //std::copy(std::begin(prob), std::end(prob), std::ostream_iterator<double>(cout, ", "));
            //cout << "}" << endl;
        }
        //for(auto& p : h2)
        //{
        //    cout << p.first << " : " << p.second << endl;
        //}
        //cout << endl;
        plot(h1, string("H1_Line_")+std::to_string(lineno));
        plot(h2, string("H2_Line_")+std::to_string(lineno));
        plot(h3, string("H3_Line_")+std::to_string(lineno));
        plot(h4, string("H4_Line_")+std::to_string(lineno));
        plot(h5, string("H5_Line_")+std::to_string(lineno));
        cout << endl;

    }

    return 0;
}
