#include <iostream>
using namespace std;

__interface IWorker {
public:
	virtual IWorker* SetNextWorker(IWorker* worker) = 0;
	virtual string Execute(string command) = 0;
};

class AbstractWorker : public IWorker {
private:
	IWorker* next_worker;
public:
	AbstractWorker() : next_worker(nullptr){}
	IWorker* SetNextWorker(IWorker* worker) override {
		next_worker = worker;
		return worker;
	}
	string Execute(string command) override {
		if (next_worker)
			return next_worker->Execute(command);
		return{};
	}
};

class Designer : public AbstractWorker {
public:
	string Execute(string command) override {
		if (command == "design a house")
			return "The designer executes the command: " + command;
		else
			return AbstractWorker::Execute(command);
	}

};

class Carpenters : public AbstractWorker {
public:
	string Execute(string command) override {
		if (command == "brick")
			return "The carpenter followed the command: " + command;
		else
			return AbstractWorker::Execute(command);
	}
};

class FinishWorker : public AbstractWorker {
public:
	string Execute(string command) override {
		if (command == "wallpaper")
			return "The interior construction worker executed the command: " + command;
		else
			return AbstractWorker::Execute(command);
	}
};

void GiveCommand(IWorker* worker, string command) {
	string str = worker->Execute(command);
	if (str.empty()) {
		cout << command << "- no one knows how to do\n";
	}
	else {
		cout << str << "\n";
	}
}

int main() {
	Designer* designer = new Designer();
	Carpenters* carpenters = new Carpenters();
	FinishWorker* finish = new FinishWorker();

	designer->SetNextWorker(carpenters)->SetNextWorker(finish);
	GiveCommand(designer, "design a house");
	GiveCommand(designer, "brick");
	GiveCommand(designer, "wallpaper");

	GiveCommand(designer, "wire");
}