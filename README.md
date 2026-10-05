# philosophers

> 42 Common Core · Rank 03

A solution to the classic **dining philosophers** problem: philosophers sit at a round table, alternately eating, sleeping and thinking, and must share forks without dying of starvation or causing a deadlock.

## Key concepts
- Threads with `pthread_create` / `pthread_join`
- Mutexes to protect forks, shared state and output
- Avoiding deadlocks and data races
- A monitor that detects a philosopher's death within 10 ms
- Precise timing with `gettimeofday` and `usleep`

## Usage
```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo 5 800 200 200
```
