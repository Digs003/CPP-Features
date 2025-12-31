#include <list> 
#include <algorithm>
#include <future>

//sequential
template<typename T>
std::list<T> sequential_quicksort(std::list<T> input)
{
  if(input.empty())
  {
    return input;
  }
  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  const T& pivot = *result.begin();
  auto divide_point = std::partition(input.begin(), input.end(),
                            [&](const T& t){ return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
  auto new_lower = sequential_quicksort(std::move(lower_part));
  auto new_higher = sequential_quicksort(std::move(input));
  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower);
  return result;
}

//parallel
template<typename T>
std::list<T> parallel_quicksort(std::list<T> input)
{
  if(input.empty())
  {
    return input;
  }
  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  const T& pivot = *result.begin();
  auto divide_point = std::partition(input.begin(), input.end(),
                            [&](const T& t){ return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
  
  auto new_lower = std::async(&parallel_quicksort<T>, std::move(lower_part));
  auto new_higher = parallel_quicksort(std::move(input));
  
  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower.get());
  return result;
}
