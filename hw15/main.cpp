/**
 * @brief CSE 471 Homework 15
 *
 * @par
 * Copyright Jeremy Wright (c) 2013
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wparentheses"

#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <boost/filesystem.hpp>
#include <boost/svg_plot/svg_2d_plot.hpp>
  using boost::svg::svg_2d_plot;

#include <boost/svg_plot/show_2d_settings.hpp>
// Only needed for showing which settings in use.

#include <boost/quan/unc_init.hpp>
#include <boost/assert.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
  using std::cout;
  using std::endl;
  using std::boolalpha;
#include <map>
  using std::map;
#include <cmath>
  using std::sqrt;
#include <string>
  using std::string;

#include <regex>

// using namespace boost::svg;
// may be *very convenient* if using any SVG named colors,
// to avoid writing
  using boost::svg::red;
  using boost::svg::yellow;
  using boost::svg::orange;
  using boost::svg::blue;
  // and other enum options used:
  using boost::svg::square;
  // for every color used.

double f(double x)
{
  return sqrt(x);
}

double g(double x)
{
  return -2 + x*x;
}

double h(double x)
{
  return -1 + 2 * x;
}

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
        {Bag1, {1.00, 0.50}},
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
    cout << "P(lime|Bag"<< bag << ")=" << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}

double p(cherry_type, Bag bag)
{
    double d = candy_dist.at(bag).first;
    cout << "P(cherry|Bag" << bag << ")=" << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}

double p(Bag bag)
{
    double d = apriori.at(bag); 
    cout << "P(bag"<< bag << ")=" << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}

double p(data_type, Bag bag)
{
    double d = pow(p(lime_type(), bag), num_limes) * pow(p(cherry_type(), bag), num_cherries);
    cout << "P(data|bag"<< bag << ")=" << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}

double p(data_type)
{
    // p(data) = \Sigma_B ( p(data | B_i) * p(B_i)
    double d = p(data_type(), Bag1) * p(Bag1);
    cout << "P(data) " << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;

}


double p(Bag bag, data_type)
{
    // p(bag_i | Data) => p(data | bag_i)*p(bag_i)/p(data)
    double d = (p(data_type(), bag) * p(bag)) / p(data_type());
    cout << "P(bag" << bag << "|data) " << d << "\n";
    BOOST_VERIFY( d >= 0 && d <= 1 );
    return d;
}


double p(lime_type, data_type)
{
    // 
    // \sigma_bags(p(lime, Bag_i | data))
    //
    std::vector<double> partials(bags.size());
    std::transform(begin(bags), end(bags), begin(partials), [](Bag b){ return  p(lime_type(), b)*p(b, data_type()); });
    double a = std::accumulate(begin(partials), end(partials), 0 );
    BOOST_VERIFY( a >= 0 && a <= 1 );
    return a;

    /*
    p(lime_type(), Bag2)*p(Bag2, data_type()) +
    p(lime_type(), Bag3)*p(Bag3, data_type()) +
    p(lime_type(), Bag4)*p(Bag4, data_type()) +
    p(lime_type(), Bag5)*p(Bag5, data_type());
    */

        
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
    while(fin >> line)
    {
        if(line == "l")
            process(lime_type());
        if(line == "c")
            process(cherry_type());
        cout << "Probability: " << p(lime_type(), data_type()) << endl << endl;
    }

    return 0;



    try
    {
        // Some containers for (sorted) sample data.
        map<double, double> data1;
        map<double, double> data2;
        map<double, double> data3;

        for(double i = -5; i <= 10.; i += 1.)
        { // Several data points for each function.
            data1[i] = f(i);
            data2[i] = g(i);
            data3[i] = h(i);
            // List if desired:
            // cout << i << ' '<< data1[i] << ' ' << data2[i] << ' '<< data3[i] << endl;
        }

        setUncDefaults(std::cout);
        svg_2d_plot my_plot;
        // Uses most defaults, but scale settings are usually sensible.

        // Add the data series to the plot:
        my_plot.title("demo_2d_simple");
        cout << " my_plot.title() " << my_plot.title() << endl;
        my_plot.x_label("X-axis").y_label("Y-axis"); // Note chaining.

        std::string s = my_plot.title();

        my_plot.plot(data1, "Sqrt(x)").fill_color(red);
        my_plot.plot(data2, "-2 + x^2").fill_color(orange).size(5);
        my_plot.plot(data3, "-1 + 2x").fill_color(yellow).bezier_on(true).line_color(blue).shape(square);
        cout << " my_plot.title() " << my_plot.title() << endl;

        my_plot.write("./demo_2d_simple.svg");
        cout << " my_plot.title() " << my_plot.title() << endl;

        show_2d_plot_settings(my_plot);
    }
    catch(const std::exception& e)
    {
    std::cout <<
      "\n""Message from thrown exception was:\n  " << e.what() << std::endl;
  }
  return 0;
} // int main()


/*

Output:

Compiling...
demo_2d_simple.cpp
Linking...
Embedding manifest...
Autorun "j:\Cpp\SVG\debug\demo_2d_simple.exe"
 my_plot.title() demo_2d_simple title
 my_plot.title() demo_2d_simple title
 my_plot.title()
axes_on true
background_border_width 2
background_border_color RGB(255,255,0)
background_color RGB(255,255,255)
image_border_margin() 10
image_border_width() 2
coord_precision 3
copyright_date
copyright_holder
description
document_title
image_x_size 500
image_y_size 400
legend_on false
legend_place 2
legend_top_left -1, -1, legend_bottom_right -1, -1
legend_background_color blank
legend_border_color RGB(255,255,0)
legend_color blank
legend_title
legend_title_font_size 14
legend_font_weight
legend_width 0
legend_lines true
license_on false
license_reproduction permits
license_distribution permits
license_attribution requires
license_commercialuse permits
plot_background_color RGB(255,255,255)
plot_border_color RGB(119,136,153)
plot_border_width 2
plot_window_on true
plot_window_x 70.2, 488
plot_window_x_left 70.2
plot_window_x_right 488
plot_window_y 57, 338
plot_window_y_top 57
plot_window_y_bottom 338.2
title_on true
title ""
title_color blank
title_font_alignment 2
title_font_decoration
title_font_family Verdana
title_font_rotation 0
title_font_size 18
title_font_stretch
title_font_style
title_font_weight
x_value_precision 3
x_value_ioflags 200 IOS format flags (0x200) dec.
y_value_precision 3
y_value_ioflags 200 IOS format flags (0x200) dec.
x_max 10
x_min -10
x_axis_on true
x_axis_color() RGB(0,0,0)
x_axis_label_color RGB(0,0,0)
x_axis_value_color RGB(0,0,0)
x_axis_width 1
x_label_on true
x_label X-axis
x_label_color blank
x_label_font_family Verdana
x_label_font_size 14
x_label_units
x_label_units_on false
x_major_labels_side left
x_major_label_rotation 0
x_major_grid_color RGB(200,220,255)
x_major_grid_on false
x_major_grid_width 1
x_major_interval 2
x_major_tick 2
x_major_tick_color RGB(0,0,0)
x_major_tick_length 5
x_major_tick_width 2
x_minor_interval 0
x_minor_tick_color RGB(0,0,0)
x_minor_tick_length 2
x_minor_tick_width 1
x_minor_grid_on false
x_minor_grid_color RGB(200,220,255)
x_minor_grid_width 0.5
x_range() -10, 10
x_num_minor_ticks 4
x_ticks_down_on true
x_ticks_up_on false
x_ticks_on_window_or_axis bottom
y_axis_position y_axis_position intersects X axis (X range includes zero)
x_axis_position x_axis_position intersects Y axis (Y range includes zero)
y_label_on true
y_label_axis Y-axis
y_axis_color RGB(0,0,0)
y_axis_label_color RGB(0,0,0)
y_axis_on true
axes_on true
y_axis_value_color RGB(0,0,0)
y_axis_width 1
y_label Y-axis
y_label_color blank
y_label_font_family Verdana
y_label_font_size 14
y_label_on true
y_label_units
y_label_units_on false
y_label_width 0
y_major_grid_on false
y_major_grid_color RGB(200,220,255)
y_major_grid_width 1
y_major_interval 2
y_major_labels_side bottom
y_major_label_rotation 0
y_major_tick_color RGB(0,0,0)
y_major_tick_length  5
y_major_tick_width  2
y_minor_grid_on false
y_minor_grid_color  RGB(200,220,255)
y_minor_grid_width 0.5
y_minor_interval 0
y_minor_tick_color RGB(0,0,0)
y_minor_tick_length 2
y_minor_tick_width 1
y_range() -10, 10
y_num_minor_ticks
y_ticks_left_on true
y_ticks_right_on false
y_ticks_on_window_or_axis left
y_max 10
y_min -10
data lines width 2




*/
