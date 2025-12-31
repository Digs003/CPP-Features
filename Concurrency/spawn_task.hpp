#include<future>
#include<thread>
#include<utility>
#include<type_traits>
#include<functional>

template<typename F, typename... Args>
std::future<std::invoke_result_t<F,Args...>> spawn_task(F&& f, Args&&... args)
{
  using ReturnType = std::invoke_result_t<F,Args...>;
  std::packaged_task<ReturnType()> task(
      [func = std::forward<F>(f),
        ...params = std::forward<Args>(args)]() mutable {
        return std::invoke(func, std::move(params)...);
        }
  );
  std::future<ReturnType> result = task.get_future();
  std::thread(std::move(task)).detach();
  return result;
}
