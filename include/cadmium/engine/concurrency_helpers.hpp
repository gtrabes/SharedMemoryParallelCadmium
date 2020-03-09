/**
 * Copyright (c) 2019, Juan Lanuza
 * Carleton University, Universidad de Buenos Aires
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CADMIUM_CONCURRENCY_HELPERS_HPP
#define CADMIUM_CONCURRENCY_HELPERS_HPP

#include <vector>
#include <functional>
#include <future>
#include <chrono>

namespace cadmium {
    namespace concurrency {
        /*
         * for_each that runs using a thread_pool (assumed without running tasks),
         * and waits por all tasks to finish until it returns
         */
/*    	template<typename ITERATOR, typename FUNC>
            void concurrent_for_each(boost::basic_thread_pool& threadpool, ITERATOR first, ITERATOR last, FUNC& f) {
              std::vector<std::future<void> > task_statuses;

              for (ITERATOR it = first; it != last; it++) {
                  std::packaged_task<void()> task(std::bind<void>(f, *it));
                  task_statuses.push_back(task.get_future());

                  threadpool.submit(std::move(task));
              }
              auto future_ready = [](auto& f) -> bool { return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready; };
              while(! std::all_of(task_statuses.begin(), task_statuses.end(), future_ready) ){
                  // if there are tasks in the threadpool queue, the main thread executes one
                  threadpool.schedule_one_or_yield();
              }
              //when concurrent_for_each end threadpool queue is empty
            }
*/

        template<class T, typename Function>
        void parallel_for_each(std::vector< T> & obj, Function f) {
        	int size = obj.size();

        	#pragma omp parallel for firstprivate(f) shared(obj)
        		for (int i = 0; i < size; i++) {
        			f(obj[i]);
        		}
        }

    }
}

#endif //CADMIUM_CONCURRENCY_HELPERS_HPP
