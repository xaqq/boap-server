#include "BehaviorTree.h"
using namespace BehaviorTree;

	template<>
	BEHAVIOR_STATUS BoolCondition<NoClass>::execute(void* agent)
	{
		if ((*func2)() == check)
			return BT_SUCCESS;
		else
			return BT_FAILURE;
	}



	template<>
	float FloatCondition<NoClass>::getObjVal(void* agent)
	{
		return (*func2)();
	}


	template<>
	BEHAVIOR_STATUS FunctionCall<NoClass>::execute(void* agent)
	{
		(*func2)(arg);
		return BT_SUCCESS;
	}


	template<>
	BEHAVIOR_STATUS IntCondition<NoClass>::execute(void* agent)
	{
		bool status;
		switch (test)
		{
		case LESS_THAN:		status = ((*func2)() < val); break;
		case GREATER_THAN:	status = ((*func2)() > val); break;
		case LESS_OR_EQ:	status = ((*func2)() <= val); break;
		case GREATER_OR_EQ: status = ((*func2)() >= val); break;
		case EQUAL:			status = ((*func2)() == val); break;
		case NOT_EQUAL:		status = ((*func2)() != val); break;
		}

		if (status)
			return BT_SUCCESS;
		else
			return BT_FAILURE;
	}
