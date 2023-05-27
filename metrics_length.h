#pragma once

#include <string>
#include <type_traits>
#include <ratio>
#include <utility>
#include <ostream>

template<typename Metric, typename OtherMetric>
struct min_metric
{
	min_metric(){}
};

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
							 (std::ratio_less_equal_v<Metric, OtherMetric>) ?
							  Metric::num : OtherMetric::num,
							 (std::ratio_less_equal_v<Metric, OtherMetric>) ?
							  Metric::den : OtherMetric::den>;

		
		intmax_t my_value = (std::ratio_less_equal_v<Metric, ResultMetric>) ? 
							 m_value : m_value * Metric::num / Metric::den;

		
		intmax_t other_value = (std::ratio_less_equal_v<OtherMetric, ResultMetric>) ?
								other.m_value : other.m_value * OtherMetric::num / OtherMetric::den;

		
		intmax_t result_value = (my_value + other_value);

		return metrics_length<ResultMetric>{ result_value };
	}
	
	template<typename OtherMetric>
	auto operator-(const metrics_length<OtherMetric>& other)
	{
		using ResultMetric = std::ratio<
							 (std::ratio_less_equal_v<Metric, OtherMetric>) ?
							  Metric::num : OtherMetric::num,
							 (std::ratio_less_equal_v<Metric, OtherMetric>) ?
							  Metric::den : OtherMetric::den>;

		intmax_t my_value = (std::ratio_less_equal_v<Metric, ResultMetric>) ? 
							 m_value : m_value * Metric::num / Metric::den;

		intmax_t other_value = (std::ratio_less_equal_v<OtherMetric, ResultMetric>) ?
								other.m_value : other.m_value * OtherMetric::num / OtherMetric::den;
		
		intmax_t result_value = (my_value - other_value);

		return metrics_length<ResultMetric>{result_value};
	}

public:
	intmax_t m_value;
};

template<typename MetricT>
std::ostream& operator<<(std::ostream& ostrm, const metrics_length<MetricT>& metric)
{
	return ostrm << metric.m_value;
}