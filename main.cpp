#include <iostream>
#include <fstream> // Used for file streaming.
#include <sstream> // Only used for converting int to string.
#include <stdio.h> // For removing files.
#include <cstdlib> // For clearing the screen.

using namespace std;




/*******************************************************************************************************************************************************/
class student
{
private:
	string name[2];
	int dateOfBirth[3], age, rollnum, coursenum;
	string address[4];
	string course[10];
	char grade[10];
public:
	void writeData		();
	bool readData		();
	void add			( int rolln );
	void displayByRoll	();
	void edit			();
	void setName		();
	void setRoll		( int r );
	void setDateOfBirth	();
	void setAddress		();
	void setCourses		();
	void removeit 		();
	
} stud[500];
/*******************************************************************************************************************************************************/




void menu();
void roll();
void displayByName ( string name[] );
void displayAll();
void avg ( string course, int newMarks ); int avg ( string course );




/*******************************************************************************************************************************************************/
int main()
{
	cout<<"**************************************"<<endl;
	cout<<" Welcome to Student Management System"<<endl;
	cout<<"**************************************"<<endl;
	//cout<<"Test 2"<<endl;
	cout<<endl;
	while (1)
	{
		cout<<"Press 1 to go to Menu, press 2 to Exit."<<endl;
		int temp; cin>>temp;
		switch (temp)
		{
			case 1:
				menu();
				break;
			case 2:
				cout<<"Exiting.";
				return 0;
		}
	}
}
/*******************************************************************************************************************************************************/




// THE MAIN MENU
/*******************************************************************************************************************************************************/
void menu()
{
	//Main menu.
	system("CLS");
	cout<<"Please enter:\n 1 To Add a student.\n 2 To Display/Search a student's data. \n 3 To Display names of all students. \n 4 Average stuff."<<endl;
	int menu; cin>>menu;
	switch (menu)
	{
	case 1:
		cout<<endl;
		roll();
		break;
	case 2:
		system("CLS");
		cout<<"Do you want to search by Name or by Roll Number?"<<endl<<"Enter:"<<endl<<endl;
		cout<<"1 To search by Name."<<endl;
		cout<<"2 To search by Roll number."<<endl<<endl;
		int searchtemp; cin>>searchtemp;
		if ( searchtemp == 1 )
		{
			string name[2];
			cout<<"Enter first name:\t\t"; cin>>name[0];
			cout<<"Enter last name:\t\t"; cin>>name[1];
			displayByName( name );
		} else 
		if ( searchtemp == 2 )
		{
			int rollnum;
			cout<<endl<<"Enter roll number:\t"; cin>>rollnum;
			stud[rollnum].setRoll( rollnum );
			stud[rollnum].displayByRoll ();
		}
		break;
	case 3:
		displayAll();
		break;
	case 4:
		cout<<"Enter Subject Name"<<endl; string subject; cin>>subject;
		cout<<"Average is: "<< avg ( subject ) <<endl;
		break;
	}
}
/*******************************************************************************************************************************************************/




// ROLL NUMBER GENERATOR
/*******************************************************************************************************************************************************/
void roll()
{
	int rollnumber;
	ifstream roll("roll.txt");
	if (roll)								// If roll.txt already exists.
	{
		ifstream roll ("roll.txt");			// Open the file.
		while( roll>>rollnumber )			// Read roll number.
		{
			rollnumber++;					// Increase roll number.
			ofstream roll;
			roll.open ("roll.txt");
			roll<<rollnumber;				// Write it back in the file.
		}
		roll.close();
		stud[ rollnumber ].add( rollnumber );

	} else									// If roll.txt does not exist.
	{
		ofstream roll;						// Create a file named roll.txt.
		roll.open ("roll.txt");				// Open the file.
		rollnumber=1;
		roll << rollnumber;					// Write the roll number '1'.
		roll.close();
		stud[ rollnumber ].add( rollnumber );
	}
}
/*******************************************************************************************************************************************************/




// READ / WRITE DATA
/*******************************************************************************************************************************************************/
void student::writeData()
{
	system("CLS");
	cout<<"Making a file for roll number "<<rollnum<<endl;;

	// Converting int to string.
	string rollString;
	stringstream convert;
	convert << rollnum;
	rollString = convert.str();
	
	// Adding ".txt" to the string.
    rollString += ".txt"; 
    
	// Making a file
	ofstream file;
    file.open(rollString.c_str());

	// Writing in the file.
	file <<name[0]<<endl<<name[1]<<endl<<dateOfBirth[0]<<endl<<dateOfBirth[1];
	file <<endl<<dateOfBirth[2]<<endl<<age<<endl<<address[0]<<endl<<address[1];
	file <<endl<<address[2]<<endl<<address[3]<<endl<<coursenum<<endl;
	for (int i=0; i<coursenum; i++)
	{
		file <<course[i] <<endl <<grade[i] <<endl;
	}
	file.close();

	cout<<"File created."<<endl<<endl<<endl;
}



bool student::readData()
{
	system("CLS");
	cout<<"Reading file of roll number:\t"<<rollnum<<endl<<endl;
	
	// Converting int to string.
	string rollnumber;
	stringstream convert;
	convert << rollnum;
	rollnumber = convert.str();
	
	// Adding ".txt" to the file.
	rollnumber += ".txt";
	
	// Reading from the file.
	ifstream file ( rollnumber.c_str() );
	if (file)
	{	
		file>>name[0]>>name[1]>>dateOfBirth[0]>>dateOfBirth[1]>>dateOfBirth[2]
			>>age>>address[0]>>address[1]>>address[2]>>address[3]>>coursenum;
			
		for (int i=0; i<coursenum; i++)
		{
			file>>course[i]>>grade[i];
		}

		file.close();
		cout<<endl<<endl;
		return true;
	} else
	{
		cout<<"Error: File not found / Unable to open file."<<endl<<endl<<endl;
		return false;
	}
}
/*******************************************************************************************************************************************************/




/*******************************************************************************************************************************************************/

void avg ( string course, int newMarks )
{
	int totalMarks, rollnumber = 0;
	course += ".txt";
	
	ifstream courseFile( course.c_str() );
	if ( courseFile )										// If *subject* .txt already exists.
	{
		ifstream courseFile (course.c_str());				// Open the file.
		while( courseFile >> rollnumber >> totalMarks )		// Read roll number and marks.
		{
			totalMarks = totalMarks + newMarks;				// Marks
			rollnumber++;									// Increase roll number.
			
			ofstream courseFile;
			courseFile.open ( course.c_str() );
			courseFile << rollnumber <<endl<< totalMarks;			// Write it back in the file.
		}
		courseFile.close();
		
	} else													// If roll.txt does not exist.
	{
		ofstream courseFile;								// Create a file named *subject* .txt.
		courseFile.open ( course.c_str() );					// Open the file.
		
		totalMarks = newMarks;
		rollnumber++;
		
		courseFile << rollnumber <<endl<< totalMarks;				// Write the roll number '1'.
		courseFile.close();
	}
}

int avg ( string course )
{
	int totalMarks=0, rollnumber=0;
	course += ".txt";
	
	ifstream courseFile( course.c_str() );
	if ( courseFile )										// If *subject* .txt already exists.
	{
		ifstream courseFile (course.c_str());				// Open the file.
		
		courseFile >> rollnumber >> totalMarks;
		
		courseFile.close();
		
		return totalMarks/rollnumber;
		
	} else													// If roll.txt does not exist.
	{
		cout<<"Subject file not found."<<endl;
	}
}
/*******************************************************************************************************************************************************/




// SET-VALUE FUNCTIONS
/*******************************************************************************************************************************************************/
void student::setRoll ( int r )
{
	rollnum = r;
}

void student::setName()
{
	string n [2];
	
	LOOP:

	cout<<endl<<"Name"<<endl<<endl;
	cout<<"First name:\t";	cin>>n [0];
	cout<<"Last name:\t";	cin>>n [1];
		
	name[0] = n [0]; name[1] = n [1];
	cout<<endl;
}

void student::setDateOfBirth()
{
	int dob[3] = { 0, 0, 0 };
	cout<<endl<<"Date of birth"<<endl<<endl;
	cout<<"Day:\t\t";		cin>>dob[0];	dateOfBirth[0] = dob [0];
	cout<<"Month:\t\t";		cin>>dob[1];	dateOfBirth[1] = dob [1];
	cout<<"Year:\t\t";		cin>>dob[2];	dateOfBirth[2] = dob [2];
	cout<<endl;

	if ( dob[0]<1 || dob[0]>31 || dob[1]<1 || dob[1]>12 || dob[2]<1 )
	{
		cout<<"Please enter valid values."<<endl;
		stud[rollnum].setDateOfBirth();
	}
	

	//Age.
	age=(2017*12-((dob[2]*12)+dob[1]))/12; //Only accurate for months.
}

void student::setAddress()
{
	string addr[4];
	cout<<endl<<"Address"<<endl<<endl;
	cout<<"City:\t\t";			cin>>addr[0];	address[0] = addr [0];
	cout<<"Colony:\t\t";		cin>>addr[1];	address[1] = addr [1];
	cout<<"Street:\t\t";		cin>>addr[2];	address[2] = addr [2];
	cout<<"House:\t\t";			cin>>addr[3];	address[3] = addr [3];
	cout<<endl;
}

void student::setCourses()
{
	
	cout<<endl<<"Enter number of courses (maximum 10):\t"; int coursnum; cin>>coursnum; cout<<endl; 
	coursenum = coursnum;
	string cours[coursnum];
	int marks[coursnum];
	if ( coursnum <= 10 && coursnum > 0 )
	{

		for (int temp1=0; temp1<coursnum; temp1++)
		{
			cout<<"Enter name of course "<<temp1+1<<":\t\t\t";	cin>>cours[temp1]; course[temp1] = cours[temp1];
			cout<<"Enter marks in that course.\t\t";			cin>>marks[temp1];
			if (marks[temp1] <= 100 && marks[temp1] >= 80)
			{
				grade [temp1] = 'A';
			} else if  (marks[temp1] <= 79 && marks[temp1] >= 60)
			{
				grade [temp1] = 'B';
			} else if (marks[temp1] <= 59 && marks[temp1] >= 50)
			{
				grade [temp1] = 'C';
			} else if (marks[temp1] <= 49 && marks[temp1] >= 40)
			{
				grade [temp1] = 'D';
			} else if (marks[temp1] <= 39)
			{
				grade [temp1] = 'F';
			}
			
			avg ( cours[temp1] , marks[temp1] );
		}
	}  else
	{
		cout<<"Number of courses must be equal to or less than 10 and greater than 0."<<endl;
		stud[rollnum].setCourses();
	}
}
/*******************************************************************************************************************************************************/




// ADDING A NEW STUDENT
/*******************************************************************************************************************************************************/
void student::add( int rolln )
{
	system("CLS");
	rollnum = rolln;
	
	cout<<"Adding a new Student with roll number: "<<rollnum<<endl;
	cout<<"Please enter the following data about the student: "<<endl<<endl;

	setName();
	setDateOfBirth();
	setAddress();
	setCourses();
	
	writeData ();
}
/*******************************************************************************************************************************************************/




// EDITING DATA OF A STUDENT
/*******************************************************************************************************************************************************/
void student::edit()
{
	system("CLS");
	cout<<"Edit data:"<<endl<<endl;
	cout<<"Enter 1 to edit a certain field, Enter 2 to edit all data."<<endl;
	int menu=0; cin>>menu;
	if ( menu == 1 )
	{
		cout<<"Enter 1 to edit Name, 2 to edit Date of Birth, 3 to edit Address, 4 to edit Courses."<<endl;
		int choose = 0; cin>>choose;
		switch (choose)
		{	
			case 1:
				setName();
				break;
			case 2:
				setDateOfBirth();
				break;
			case 3:
				setAddress();
				break;
			case 4:
				setCourses();
				break;
		}
	} else 
	if ( menu == 2 )
	{
		setName();
		setDateOfBirth();
		setAddress();
		setCourses();
	}
	
	writeData();
}
/*******************************************************************************************************************************************************/




// DISPLAYING / SEARCHING
/*******************************************************************************************************************************************************/
void displayByName( string name[] )
{
	int rollnum1;
	string nametemp[2];
	ifstream file ("roll.txt");
	if (file)
	{
		while (file>>rollnum1)
		{
			for (int i=1; i<=rollnum1; i++)
			{
				string rollString;
				stringstream convert;
				convert << i;
				rollString = convert.str();
			    rollString += ".txt"; // important to create .txt file.
				ifstream nameo (rollString.c_str());
				if (nameo)
				{
					while (nameo>>nametemp[0]>>nametemp[1])
					{
						if(name[0]==nametemp[0] && name[1]==nametemp[1])
						{
							stud[i].displayByRoll();
						} else
						{
							cout<<"Error: File not found / Unable to open file."<<endl;
						}
					}
				} else
				{
					cout<<"Error: File not found / Unable to open file."<<endl;
				}
			}
		}
	}
}



void student::displayByRoll()
{
	bool check = readData();
	if ( check == true )
	{
		cout<<"Name\t\t\t"<<name[0]<<" "<<name[1]<<endl<<endl;
		cout<<"Date of birth\t\t";
		cout<<dateOfBirth[0]<<" - "<<dateOfBirth[1]<<" - "<<dateOfBirth[2]<<endl<<endl;
		cout<<"Age\t\t\t"<<age<<endl<<endl;
		cout<<"Address:"<<endl;
		cout<<"House "<<address[3]<<", "<<"Street "<<address[2]<<
		", "<<address[1]<<" Colony"<<", "<<address[0]<<endl<<endl;
		for ( int temp2=0; temp2<coursenum; temp2++ )
		{
			cout<<"Grade in "<<course[temp2]<<" is "<<grade[temp2]<<endl;
		}
	
		cout<<endl<<endl<<"Enter 1 to Edit or 2 to Delete this file. Enter 3 to go back."<<endl<<endl;
		int menu; cin>>menu;
		switch (menu)
		{
		case 1:
			cout<<endl;
			edit();
			writeData();
			cout<<"New data:"<<endl<<endl; stud[rollnum].displayByRoll();
			break;
		case 2:
			removeit();
			cout<<endl<<endl;
			break;
		case 3:
			break;
		}
	}
}



void displayAll()
{
	system("CLS");
	cout<<endl<<"All Students."<<endl<<endl;
	cout<<"Roll\tName"<<endl<<endl;
	int rollnum1; string nametemp[2];
	ifstream file ("roll.txt");
	if (file)
	{
		while (file>>rollnum1)
		{
			for (int i=1; i<=rollnum1; i++)
			{
				string rollString;
				stringstream convert;
				convert << i;
				rollString = convert.str();
			    rollString += ".txt"; // important to create .txt file.
				ifstream nameo (rollString.c_str());
				if (nameo)
				{
					while (nameo>>nametemp[0]>>nametemp[1])
					{
						cout<<i<<"\t"<<nametemp[0]<<" "<<nametemp[1]<<endl;
						nameo.close();
					}
				} else
				{
					cout<<i<<endl;
				}
			}
		}
	}
	cout<<endl;
}
/*******************************************************************************************************************************************************/




// DELETING FILES
/*******************************************************************************************************************************************************/
void student::removeit()
{
	string rollnumber;
	stringstream convert;
	convert << rollnum;
	rollnumber = convert.str();
	rollnumber += ".txt";
	ifstream file ( rollnumber.c_str() );

	
	string name[2];
	if (file)
	{
		while( file>>name[0]>>name[1] )
		file.close();
		cout<<endl<<"Do you wish to delete the file of "<<name[0]<<" "<<name[1]<<"? (Y/N)"<<endl;
		char temp; cin>>temp;
		if (temp=='y'||temp=='Y')
		{
			remove(rollnumber.c_str()); //Deletes the file.
			cout<<endl<<"Student's file has been deleted."<<endl;
		} else
		{
			cout<<endl<<"The file has not been deleted."<<endl;
		}
	} else
	{
		cout<<endl<<"Error: File not found / Unable to access file."<<endl;
	}
}
