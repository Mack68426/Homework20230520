#pragma once

#include <string>
#include <type_traits>
#include <ratio>
#include <utility>
#include <ostream>


template<typename Metric>
class metrics_length
{
public:
	metrics_length(intmax_t value)
		: m_value(value)
	{
	}

	template<typename OtherMetric>
	auto operator+(const metrics_length<OtherMetric>& other)
	{
		using ResultMetric = std::ratio<
							 (Metric::num <= OtherMetric::num) ? Metric::num : OtherMetric::num,
							 (Metric::den > OtherMetric::den) ? Metric::den : OtherMetric::den>;

		// 1 km -> 1*1000m
		// 10 cm 
		intmax_t my_value =  std::ratio_less_equal_v<Metric, ResultMetric> ?
							 m_value : m_value * Metric::num / Metric::den;

		// 100 m
		// 100 m -> 100*100cm
		intmax_t other_value = std::ratio_less_equal_v<OtherMetric, ResultMetric> ?
							   other.m_value : 
							   other.m_value * ResultMetric::num / ResultMetric::den;

		// 1000 + 100m = 1100
		// 10 + 10000 = 10010
		intmax_t result_value = (my_value + other_value);

		return metrics_length<ResultMetric>
		{
			result_value
		};
	}
	

public:
	intmax_t m_value;
};

template<typename MetricT>
std::ostream& operator<<(std::ostream& ostrm, const metrics_length<MetricT>& metric)
{
	return ostrm << metric.m_value;
}