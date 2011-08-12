
#ifndef ATTRIBUTE_STATS_HPP
#define ATTRIBUTE_STATS_HPP
// mapnik
#include <mapnik/config.hpp>
// #include <mapnik/ctrans.hpp>
// #include <mapnik/params.hpp>
// #include <mapnik/feature.hpp>
// #include <mapnik/query.hpp>
// #include <mapnik/feature_layer_desc.hpp>
// boost
#include <boost/utility.hpp>


class MAPNIK_DECL attribute_stats : private boost::noncopyable
{
public:
    attribute_stats()
    {
        reset();
    }

    void reset()
    {
        samples_ = 0;
        min_ = 0;
        max_ = 0;
        sum_ = 0;
    }

    inline void update(double value)
    {
        samples_++;
        if (samples_ == 1)
        {
            min_ = max_ = sum_ = value;
        }
        else
        {
            if (value < min_)       min_ = value;
            else if (value > max_)  max_ = value;
            sum_ += value;
        }
    }

    inline double min() { return min_; }
    inline double max() { return max_; }
    inline double mean() { return sum_ / samples_; }
    inline unsigned long samples() { return samples_; }
    inline double sum() { return sum_; }

protected:
    unsigned long samples_;
    double min_;
    double max_;
    double sum_; // required for continuously updating mean_
};

#endif //ATTRIBUTE_STATS_HPP
