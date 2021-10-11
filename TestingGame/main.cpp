#include <iostream>
#include <conio.h>

char g_keyInput;

class Menu
{
private:
	signed char choose_;

public:
	Menu() : choose_(0) {};

	void Up()
	{
		if (choose_ > 0 && choose_ <= 4)
			choose_--;
	}

	void Down()
	{
		if (choose_ >= 0 && choose_ < 4)
			choose_++;
	}

	void Draw()
	{
		for (int i = 0; i < 5; ++i)
		{
			if (choose_ == i)
				std::cout << "[X] This is the " << i << " choose!\n";
			else
				std::cout << "[ ] This is the " << i << " choose!\n";
		}
	}
};

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(Menu*& menu) = 0;
};

class UpCommand : public Command
{
public:
	virtual void execute(Menu*& menu)
	{
		menu->Up();
	}
};

class DownCommand : public Command
{
public:
	virtual void execute(Menu*& menu)
	{
		menu->Down();
	}
};

class InputHandler
{
public:
	InputHandler()
	{
		upCommand = new UpCommand();
		downCommand = new DownCommand();
	}

	~InputHandler()
	{
		delete upCommand;
		delete downCommand;
	}

	Command* handleInput()
	{
		if (g_keyInput == 'W') return upCommand;
		else if (g_keyInput == 'S') return downCommand;

		return nullptr;
	}

private:
	Command* upCommand;
	Command* downCommand;
};


int main()
{
	Menu* myMenu = new Menu();
	InputHandler inputHandler;

	myMenu->Draw();

	while (true)
	{
		g_keyInput = toupper(_getch());
		if (g_keyInput == 27)
			break;
		Command* command = inputHandler.handleInput();
		if (command)
			command->execute(myMenu);

		system("cls");
		myMenu->Draw();
	}

	delete myMenu;
	return 0;
}