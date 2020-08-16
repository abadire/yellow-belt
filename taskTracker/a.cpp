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

	TaskStatus iter = TaskStatus::NEW;

	for (int i = task_count; i > 0;)
	{

		while (initial.count(iter) == 0)
		{
			iter = static_cast<TaskStatus>(static_cast<int>(iter) + 1);
			if (TaskStatus::DONE == iter)
			{
				goto exitLoop;
			}
		}

		if (initial[iter] > i)
		{
			info[iter] -= i;
			initial[iter] -= i;
			info[static_cast<TaskStatus>(static_cast<int>(iter) + 1)] += i;
			refreshed[static_cast<TaskStatus>(static_cast<int>(iter) + 1)] += i;
			break;
		}
		else
		{
			info[static_cast<TaskStatus>(static_cast<int>(iter) + 1)] += info[iter];
			refreshed[static_cast<TaskStatus>(static_cast<int>(iter) + 1)] += info[iter];
			i -= info[iter];
			info.erase(iter);
			initial.erase(iter);
		}
	}

	exitLoop:

	return tie(refreshed, initial);
}

void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

#ifdef LOCAL
int main()
{
  	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
  TasksInfo updated_tasks, untouched_tasks;
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 4);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << endl;
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << endl;
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);  
    cout << endl;
	  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);  
    cout << endl;
	
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}
#endif