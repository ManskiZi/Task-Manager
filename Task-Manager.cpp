#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Task class to represent individual tasks
class Task {
public:
    string description; // Description of the task
    int priorityLevel; // Priority level of the task
    Task *next; // Pointer to the next task in the list
    Task *prev; // Pointer to the previous task in the list

    // Constructor to initialize Task object with description and priority level
    Task(string des, int priority) : description(des), priorityLevel(priority), next(nullptr), prev(nullptr) {}
};

// DoublyLinkedList class to manage a list of tasks
class DoublyLinkedList {
private:
    Task *head; // Pointer to the first task in the list
    Task *tail; // Pointer to the last task in the list

public:
    // Constructor to initialize an empty list
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Method to add a new task to the end of the list
    void addTask(string des, int priority) {
        // Check if priority level is valid
        if (priority > 5) {
            cout << "priority level must be 5 or less\n";
        } else {
            Task *newTask = new Task(des, priority);

            // If list is empty, set new task as both head and tail
            if (head == nullptr) {
                head = tail = newTask;
            } else {
                tail->next = newTask;
                newTask->prev = tail;
                tail = newTask;
            }
        }
    }

    // Method to display all tasks in the list
    void display() {
        Task *current = head;

        if (current == nullptr) {
            cout << "Task folder is empty\n";
            return;
        }

        while (current != nullptr) {
            cout << "Description: " << current->description << "\n";
            cout << "Priority level: " << current->priorityLevel << "\n";

            current = current->next;
        }
    }

    // Method to delete a task with a given description
    void deleteTask(string taskDescription) {
        Task *current = head;

        // Search for the task with the given description
        while (current != nullptr && current->description != taskDescription) {
            current = current->next;
        }

        // If task is not found, print a message and return
        if (current == nullptr) {
            cout << "Task with description: " << taskDescription << " not found\n";
            return;
        }

        // Adjust pointers to remove the task from the list
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }

        // Delete the task and print a message
        delete current;
        cout << "Task with description " << taskDescription << " deleted.\n";
    }

    // Method to modify the description of a task
    void modifyTask(string taskDescription) {
        Task *current = head;
        string newDescription = "";

        // If list is empty, print a message and return
        if (current == nullptr) {
            cout << "Task folder is empty\n";
        } else if (current->next == nullptr) { // If there is only one task in the list
            cout << "Enter new description: \n";
            cin.ignore(); // Ignore newline character
            getline(cin, newDescription);
            current->description = newDescription;
        } else {
            // Search for the task with the given description
            while (current->next != nullptr && current->description != taskDescription) {
                current = current->next;
            }

            // If task is not found, print a message and return
            if (current == nullptr) {
                cout << "Task with description: " << taskDescription << " not found\n";
                return;
            }

            // Modify the description of the task
            cout << "Enter new description: \n";
            getline(cin, newDescription);
            current->description = newDescription;
        }
    }

    // Method to sort the list based on priority level using insertion sort
    void insertionSort() {
        // If list is empty or only has one task, no need to sort
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Task *sorted = nullptr; // Initialize sorted sublist
        Task *current = head;

        while (current != nullptr) {
            Task *next = current->next; // Store next task before modifying it

            if (sorted == nullptr || current->priorityLevel <= sorted->priorityLevel) {
                // Insert at the beginning of the sorted list
                current->prev = nullptr; // Set the previous pointer of the current node to nullptr, indicating it is the new head of the sorted sublist
                current->next = sorted; // Set the next pointer of the current node to point to the sorted sublist, making it the new head of the sorted sublist


                if (sorted != nullptr) {
                    // Update the previous pointer of the sorted sublist's head node to point to the current node,
                    // establishing a bidirectional link between the current node and the sorted sublist
                    sorted->prev = current;
                }
                // Set the sorted sublist's head node to the current node,
                // effectively making the current node the new head of the sorted sublist
                sorted = current;
            } else {
                // Create a temporary pointer to traverse the sorted sublist
                Task *temp = sorted;
                
                // Traverse the sorted sublist until finding the correct position for the current task
                while (temp->next != nullptr && temp->next->priorityLevel < current->priorityLevel) {
                    temp = temp->next;
                    }

                // Update the previous pointer of the current task to point to the correct position in the sorted sublist
                current->prev = temp;
                
                // Update the next pointer of the current task to maintain the correct ordering in the sorted sublist
                current->next = temp->next;

                // Update the previous pointer of the next node in the sorted sublist, if it exists
                if (temp->next != nullptr) {
                    temp->next->prev = current;
                    }

                // Update the next pointer of the previous node in the sorted sublist to point to the current node
                temp->next = current;
            }
            current = next; // Move to the next task
        }

        // Update head and tail pointers
        head = sorted;
        tail = sorted;

        while (tail->next != nullptr) {
            tail = tail->next;
        }
    }

    // Destructor to deallocate memory used by the list
    ~DoublyLinkedList() {
        Task *current = head;
        Task *nextTask;

        while (current != nullptr) {
            nextTask = current->next;
            delete current;
            current = nextTask;
        }
        head = tail = nullptr;
    }

    // Method to save tasks to a file
    void saveToFile(const string &filename) {
        ofstream file(filename);

        if (!file.is_open()) {
            cout << "Unable to open file: " << filename << "\n";
            return;
        }

        Task *current = head;

        while (current != nullptr) {
            file << current->description << ", " << current->priorityLevel << "\n";
            current = current->next;
        }

        file.close();
        cout << "Tasks saved to file: " << filename << "\n";
    }
};

// Function to display menu options
void menu() {
    cout << "Welcome precious user, what can we do for you today\n";
    cout << "[1] Add task\n";
    cout << "[2] Display task folder\n";
    cout << "[3] Remove task\n";
    cout << "[4] Modify task\n";
    cout << "[5] Sort folder\n";
    cout << "[6] Save file\n";
    cout << "[7] Exit software\n";
    cout << "Enter choice:\n";
}
int main() {
    int choice; // Variable to store user's choice
    DoublyLinkedList taskFolder; // Create an instance of DoublyLinkedList to manage tasks

    // Main menu loop
    do {
        menu(); // Display menu options
        cin >> choice; // Read user's choice

        // Switch based on user's choice
        switch (choice) {
            case 1: { // Add task
                string description;
                int priority;
                cout << "Enter task description: ";
                cin.ignore(); // Ignore the newline character
                getline(std::cin, description); // Read task description
                cout << "Enter task priority: ";
                cin >> priority; // Read task priority
                taskFolder.addTask(description, priority); // Add task to the folder
                break;
            }
            case 2: { // Display tasks
                taskFolder.display(); // Display all tasks in the folder
                break;
            }
            case 3: { // Remove task
                string description;
                cout << "Enter task description to remove: ";
                cin.ignore(); // Ignore the newline character
                getline(std::cin, description); // Read task description
                taskFolder.deleteTask(description); // Delete task from the folder
                break;
            }
            case 4: { // Modify task
                string description;
                cout << "Enter task description to modify: ";
                cin.ignore(); // Ignore the newline character
                getline(std::cin, description); // Read task description
                taskFolder.modifyTask(description); // Modify task in the folder
                break;
            }
            case 5: { // Sort folder
                taskFolder.insertionSort(); // Sort tasks in the folder based on priority
                break;
            }
            case 6: { // Save tasks to file
                string filename;
                cout << "Enter file name to save: ";
                cin >> filename; // Read file name
                taskFolder.saveToFile(filename); // Save tasks to the specified file
                break;
            }
            case 7: // Exit program
                std::cout << "Exiting program.\n";
                break;
            default: // Invalid choice
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7); // Repeat until user chooses to exit

    return 0;
}
