#pragma once
class UnexpectedActionHandler
{

public:
	enum Condition{NULL_PATH, OPEN_FILE_FAILURE };
	UnexpectedActionHandler(void);
	~UnexpectedActionHandler(void);

	void handle(Condition c);
};

