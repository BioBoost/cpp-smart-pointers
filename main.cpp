// Smart pointer automate the new and delete process
// previously needed for allocating memory on the heap.

// unique_ptr = scoped pointer, can't be copied
// shared_ptr = allows pointers to be copied (uses reference counting)
// weak_ptr = can be assigned shared_ptr but does not increase reference counter
//            (it does not keep object alive if reference count reaches 0)

#include <iostream>
#include <memory>

using namespace std;

class Entity {
  public:
    Entity(string name) : name(name) { cout << name << " entity is being constructed" << endl; }
    ~Entity(void) { cout << name << " entity is being destroyed" << endl; }

  public:
    void print(void) { cout << name << ": find me at " << this << endl; }

  private:
    string name = "";
};

int main() {
  cout << "Welcome to smart pointer demo" << endl;

  // Let's just create object on the stack to test
  Entity obj("obj");
  obj.print();

  // Second pointer to shared (see later)
  shared_ptr<Entity> anotherShared;

  // Let's create local scope with unique pointer
  {
    unique_ptr<Entity> local(new Entity("local"));
    local->print();

    unique_ptr<Entity> second = make_unique<Entity>("second");    // Preferred way apparently (has something to do with exceptions)
    second->print();

    shared_ptr<Entity> shared = make_shared<Entity>("shared");
    shared->print();
      // shared pointer goes out of scope but we'll make a second shared pointer referencing the object
    
    anotherShared = shared;
  }

  anotherShared->print();

  return 0;
}