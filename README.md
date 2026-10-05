# philosophers

> 42 Common Core · Rank 03

## Introduction
Philosophers is a 42 project based on the classic **dining philosophers problem**. The purpose is to learn the basics of threading a process: how to create threads, and how to use **mutexes** so that threads can share resources safely without data races or deadlocks.

One or more philosophers sit at a round table with a big bowl of spaghetti in the middle. There is one fork between each pair of neighbours, so there are as many forks as philosophers. Each philosopher is a thread and each fork is protected by a mutex.

- A philosopher needs **both** the fork on their left and the fork on their right to eat.
- Philosophers take turns to **eat**, then **sleep**, then **think**.
- If a philosopher goes `time_to_die` milliseconds without starting a meal, they **die** and the simulation stops.
- Philosophers don't talk to each other and don't know when another one is about to die.

The goal is to keep every philosopher alive for as long as possible.

## Arguments
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
|---|---|
| `number_of_philosophers` | Number of philosophers, and also the number of forks |
| `time_to_die` (ms) | If a philosopher hasn't started eating this long after the start of their last meal (or the start of the simulation), they die |
| `time_to_eat` (ms) | How long eating takes. A philosopher holds two forks during this time |
| `time_to_sleep` (ms) | How long sleeping takes |
| `number_of_times_each_philosopher_must_eat` (optional) | If given, the simulation stops once every philosopher has eaten at least this many times. Otherwise it stops when a philosopher dies |

## Output
Every change of state is printed as `timestamp_in_ms philosopher_number action`:
```
0 1 has taken a fork
0 1 is eating
201 1 is sleeping
401 1 is thinking
801 1 died
```
Messages never overlap, and nothing is printed after `died`.

## How it works
1. **Validation** – Checks there are 4 or 5 arguments, that each one is a positive whole number that fits in an `int`, and that there is at least 1 philosopher (and at least 1 meal, if the meal limit is given).
2. **Setup** – Creates one mutex per fork, one per philosopher (protecting the time of their last meal and their meal count), one for printing and one for the "simulation has ended" flag.
3. **Threads** – Starts one thread per philosopher. Each loops: take two forks → eat → sleep → think, stopping as soon as the simulation has ended.
4. **No deadlock** – If every philosopher picked up their left fork at the same time, all would wait forever for the right one. To prevent this, neighbours pick up their two forks in opposite order, so at least one philosopher can always get both.
5. **Monitor** – The main thread checks every philosopher about once per millisecond. When one has gone longer than `time_to_die` without eating, it prints `died` and ends the simulation, so the death is reported within a few milliseconds (for example `801 1 died` with `time_to_die` = 800). With the meal limit, it also ends the simulation once everyone has eaten enough.
6. **One philosopher** – With only one fork on the table, the philosopher takes it, can never eat, and dies after `time_to_die`.
7. **Cleanup** – All threads are joined, then every mutex is destroyed and all memory is freed.

The functions used are [`pthread_create`](https://man7.org/linux/man-pages/man3/pthread_create.3.html), [`pthread_join`](https://man7.org/linux/man-pages/man3/pthread_join.3.html), [`pthread_mutex_init`](https://man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html), [`pthread_mutex_lock` / `pthread_mutex_unlock`](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html), [`pthread_mutex_destroy`](https://man7.org/linux/man-pages/man3/pthread_mutex_destroy.3p.html), [`gettimeofday`](https://man7.org/linux/man-pages/man2/gettimeofday.2.html), [`usleep`](https://man7.org/linux/man-pages/man3/usleep.3.html), `printf`, `malloc` and `free`.

## Error handling
For invalid arguments, the program prints a message and exits with status `1`:

| Input | Message |
|---|---|
| Not 4 or 5 arguments | `./philo philo_num time_die time_eat time_sleep [nbr_meals]` |
| Not a positive whole number (`abc`, `-5`) or larger than `INT_MAX` | `Enter Integer Only` |
| 0 philosophers, or a meal limit of 0 | `Need at least 1 philosopher and 1 meal` |

## Test cases
| Command | Expected result |
|---|---|
| `./philo 1 800 200 200` | The philosopher takes one fork and dies at 800 ms |
| `./philo 5 800 200 200` | Nobody dies; runs until stopped with `Ctrl-C` |
| `./philo 5 800 200 200 7` | Nobody dies; stops once everyone has eaten 7 times |
| `./philo 4 410 200 200` | Nobody dies |
| `./philo 4 310 200 100` | A philosopher dies at about 310 ms |

## Clone
Clone the repository:
```bash
git clone https://github.com/HowardHoJiaHao/philosophers.git
```

## Compile and Run
To compile, `cd` into the cloned directory and run:
```bash
make
```

This builds the `philo` executable. Other targets: `make clean` (remove object files), `make fclean` (also remove `philo`) and `make re` (rebuild from scratch).

To run the program:
```bash
./philo 3 800 200 200 1
```

Result:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
201 2 has taken a fork
201 2 has taken a fork
201 2 is eating
201 1 is sleeping
201 3 has taken a fork
401 2 is sleeping
401 1 is thinking
401 3 has taken a fork
401 3 is eating
```
