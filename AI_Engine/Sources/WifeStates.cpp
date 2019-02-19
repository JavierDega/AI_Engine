#include "pch.h"
#include "..\Headers\WifeStates.h"

using namespace std;

void Cooking::Execute(Wife * wife)
{
	//@Cooking increases cookState iterator
	wife->m_cookState++;

	//@Log (Also reset length)
	wife->m_text = L"Cooking!";

}

void DeliveringFood::Execute(Wife * wife)
{
	//@Deposits gold in the bank
	wife->m_cookState = 0;
	
	wife->m_foodStack += 3;
	wife->m_drinkStack += 3;
	//@Log (Also reset length)
	wife->m_text = L"Mmm delicious meal!";
}
