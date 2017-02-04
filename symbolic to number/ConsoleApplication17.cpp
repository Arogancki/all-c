#include "stdafx.h"
#include <string>
#include <iostream>
#include "ConsoleApplication17.h"
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Number test1("154.656oc"), test2("888t"), test3("1.656m"), test4("344.56sp"), test5("17qa"), test6("66.6yw");
	cout << "Pierwsza czesc zadania" << endl << endl << "154.656oc = " << test1.ConvertFromSymbolic() << endl << endl << "888t = " << test2.ConvertFromSymbolic() << endl << endl << "1.656m = " << test3.ConvertFromSymbolic() << endl << endl << "344.56sp = " << test4.ConvertFromSymbolic() << endl << endl << "17qa = " << test5.ConvertFromSymbolic() << endl << endl << "66.6yw = " << test6.ConvertFromSymbolic() << endl << endl << endl << endl;

	cout << "Druga czesc zadania" << endl << endl;
	Number trillion("1t"), fiveMln("5m"), twoAndHalfSeptilion("2.5sp");
	Assert ifitis(1);
	cout << "Is 1 000 000 000 000 and trillion equal? = " << ifitis.AreEqual("1 000 000 000 000", trillion.ConvertFromSymbolic()) << endl << endl << "Is 5 000 001 and five million equal? = " << ifitis.AreEqual("5 000 001", fiveMln.ConvertFromSymbolic()) << endl << endl << "Is 2 500 000 000 000 000 000 000 000 and two and half septillion equall? = " << ifitis.AreEqual("2 500 000 000 000 000 000 000 000", twoAndHalfSeptilion.ConvertFromSymbolic()) << endl << endl;
	getchar();
}
