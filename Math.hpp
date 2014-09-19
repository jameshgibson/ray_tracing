#pragma once

template<class T>
bool epsilon_equals(const T &lhs, const T &rhs, double epsilon = 0.0000001)
{
    return std::abs(lhs - rhs) < epsilon;
}

template<class container>
typename container::value_type sum(const container &nums, typename container::value_type init = 0.0)
{
    typename container::const_iterator it = nums.begin();
    for (; it < nums.end(); ++it)
    {
	init += *it;
    }
    return init;
}


template<class container>
typename container::value_type average(const container &nums, typename container::value_type init = 0.0)
{
    return sum(nums, init) / (typename container::value_type)nums.size();
}
    
