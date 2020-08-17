#include <vector>
#include <iostream>
#include <map>

using namespace std;

#ifdef LOCAL
enum class TaskStatus
{
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

using TasksInfo = map<TaskStatus, int>;
#endif

class TeamTasks
{
public:
	const TasksInfo& GetPersonTasksInfo(const string& person) const;
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person);
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count);

private:
	map<string, TasksInfo> infos;
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const
{
	return infos.at(person);
}

void TeamTasks::AddNewTask(const string& person)
{
	++infos[person][TaskStatus::NEW];
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string& person, int task_count)
{
	TasksInfo refreshed, initial = infos[person];
	initial.erase(TaskStatus::DONE);
	TasksInfo& info = infos[person];

	for (int iter = 0; iter != 3; ++iter)
	{
		TaskStatus status = static_cast<TaskStatus>(iter);
		TaskStatus statusNext = static_cast<TaskStatus>(iter + 1);
		if (0 == initial.count(status))
		{
			continue;
		}
		else if (task_count > 0)
		{
			refreshed[statusNext] += min(initial[status], task_count);
			initial[status] -= min(initial[status], task_count);
			if (initial[status] == 0)
			{
				initial.erase(status);
			}
			info[status] -= refreshed[statusNext];
			info[statusNext] += refreshed[statusNext];
			if (info[status] == 0)
			{
				info.erase(status);
			}
			task_count -= min(refreshed[statusNext], task_count);


			// if (task_count > initial[status])
			// {


			// 	refreshed[statusNext] += initial[status];
			// 	info[statusNext] += initial[status];
			// 	task_count -= initial[status];
			// 	initial.erase(status);
			// 	info.erase(status);
			// }
			// else if (task_count == initial[status])
			// {
			// 	refreshed[statusNext] += task_count;
			// 	info[statusNext] += task_count;
			// 	task_count = 0;
			// 	initial.erase(status);
			// 	info.erase(status);
			// }
			// else
			// {
			// 	refreshed[statusNext] += task_count;
			// 	info[statusNext] += task_count;
			// 	initial[status] -= task_count;
			// 	info[status] -= task_count;
			// 	task_count = 0;
			// }
		}
	}

	// TaskStatus iter = TaskStatus::NEW;

	// while (TaskStatus::DONE != iter)
	// {

	// 	while (initial.count(iter) == 0)
	// 	{
	// 		iter = static_cast<TaskStatus>(static_cast<int>(iter) + 1);
	// 		if (TaskStatus::DONE == iter)
	// 		{
	// 			goto exitLoop;
	// 		}
	// 	}

	// 	if (task_count < 1 && 0 != initial.count(iter) && initial[iter] == 0)
	// 	{
	// 		info.erase(iter);
	// 		initial.erase(iter);
	// 	}
	// 	else if (initial[iter] > task_count)
	// 	{
	// 		info[iter] -= task_count;
	// 		initial[iter] -= task_count;
	// 		info[static_cast<TaskStatus>(static_cast<int>(iter) + 1)] += task_count;
	// 		refreshed[static_cast<TaskStatus>(static_cast<int>(iter) + 1)] += task_count;
	// 		break;
	// 	}
	// 	else
	// 	{
	// 		info[static_cast<TaskStatus>(static_cast<int>(iter) + 1)] += info[iter];
	// 		refreshed[static_cast<TaskStatus>(static_cast<int>(iter) + 1)] += info[iter];
	// 		task_count -= info[iter];
	// 		info.erase(iter);
	// 		initial.erase(iter);
	// 	}
	// }

	// exitLoop:

	return tie(refreshed, initial);
}

// void PrintTasksInfo(TasksInfo tasks_info) {
//   cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
//       ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
//       ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
//       ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
// }

void PrintTasksInfo(const TasksInfo& tasks_info) {
    if (tasks_info.count(TaskStatus::NEW)) {
        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
    }
    if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
    }
    if (tasks_info.count(TaskStatus::TESTING)) {
        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
    }
    if (tasks_info.count(TaskStatus::DONE)) {
        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
    }
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
    std::cout << "Updated: [";
    PrintTasksInfo(updated_tasks);
    std::cout << "] ";

    std::cout << "Untouched: [";
    PrintTasksInfo(untouched_tasks);
    std::cout << "] ";

    std::cout << std::endl;
}

#ifdef LOCAL
int main()
{
  	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
// TeamTasks tasks;
//   tasks.AddNewTask("Ilia");
//   for (int i = 0; i < 3; ++i) {
//     tasks.AddNewTask("Ivan");
//   }
//   cout << "Ilia's tasks: ";
//   PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
//   cout << "Ivan's tasks: ";
//   PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
//   TasksInfo updated_tasks, untouched_tasks;
  
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 4);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);
  
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 2);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);
//   cout << endl;
  
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 2);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);
//   cout << endl;
  
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 2);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);  
//     cout << endl;
	  
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 2);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);  
//     cout << endl;
	
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 2);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);

   TeamTasks tasks;
    TasksInfo updated_tasks;
    TasksInfo untouched_tasks;

    // /* TEST 1 */
    // std::cout << "Alice" << std::endl;

    // for (auto i = 0; i < 5; ++i) {
    //     tasks.AddNewTask("Alice");
    // }
    // tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    // PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

    // tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    // PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

    // tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    // PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

    // for (auto i = 0; i < 5; ++i) {
    //     tasks.AddNewTask("Alice");
    // }
    // tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
    //                                                                2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
    // PrintTasksInfo(updated_tasks, untouched_tasks);

    // PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    // std::cout << std::endl;

    // tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    // PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    // PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    // std::cout << std::endl;

    /* TEST 2 */
    std::cout << "\nJack" << std::endl;

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

    tasks.AddNewTask("Jack");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
    std::cout << std::endl;

    /* TEST 3 */
    std::cout << "\nLisa" << std::endl;

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;

    tasks.AddNewTask("Lisa");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

    return 0;
}
#endif