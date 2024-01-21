/*Code for Assignment-1 TP1 2023 - COS10007 Question 2 
Student Name - Ruchika De Zoysa 
Student ID Number - 104316170

This program reads employee details from a .txt file and performs the following functions on it.
1. Displays the employee list
2. Searches for employees 
3. Finds the employee with the maximum salary
4. Finds employees with salaries lower than 5000
5. Finds the average salary for a given company
6. Adds a new employee*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structure to hold personal details
struct personTag{
	char name[20];
	int age;
};

//Structure to hold company details
struct officialTag{
	int deptId;
	char cmpName[20];
	double salary;
};

//Structure to hold the nested structures
struct employeeTag{
	struct personTag personalInfo;
	struct officialTag officialInfo;
	struct employeeTag *next;
};

typedef struct employeeTag EMPLOYEETag;
typedef EMPLOYEETag *EMPLOYEETagPtr;

//Variables
char pName[20]; //to hold Employee name
char oName[20];// to hold Company name
int pAge;//to hold Employee age
int oId;//to hold department id
double oSalary;

//Function prototypes
void readFile(EMPLOYEETagPtr *start);
int menu();
void insert(EMPLOYEETagPtr *start, char pName[], int pAge, int oId, char oName[], double oSalary);
void displayEmployees(EMPLOYEETagPtr start);
void searchEmployee(EMPLOYEETagPtr start, char pName[]);
void findMaximum(EMPLOYEETagPtr start);
void lowerSalary(EMPLOYEETagPtr start);
void averageSalary(EMPLOYEETagPtr start, char oName[]);
void updateFile(EMPLOYEETagPtr *start, char pName[], int pAge, int oId, char oName[], double oSalary);

int main()
{
	EMPLOYEETagPtr start=NULL;//initializing start pointer to null
	readFile(&start);//reading from file
	int exit=0;//exit is a flag to end the loop
	while(exit!=1)
	{
		int option = menu();//Calling the menu function
		switch(option)
		{
			case 1 :displayEmployees(start);//calling displayEmployees function, passing start
					break;//break to avoid fall through effect
			case 2 :printf("Enter the name of the employee to search: ");//prompting user for employee name to search
					scanf("%s",pName);
					fflush(stdin);//to flush the buffer
					searchEmployee(start, pName);//calling searchEmployee, passing start & employee name
					break;
			case 3 :findMaximum(start);//calling findMaximum function, passing start
					break;
			case 4 :lowerSalary(start);//calling lowerSalary function, passing start
					break;
			case 5 :printf("Enter name of the company: ");//prompting user for company name to search for avaerage salary
					scanf("%s", oName);
					fflush(stdin);
					averageSalary(start, oName);//calling average salary function, passing company name
					break;
			case 6 :printf("Please enter the new employee\'s name: ");//prompting user for new employee name
					scanf("%s",pName);
					fflush(stdin);
					printf("Please enter the new employee\'s Age: ");//prompting user for new employee age
					scanf("%d",&pAge);
					printf("Please enter the new employee Id: ");//prompting user for new employee's department id
					scanf("%d",&oId);
					printf("Please enter the new Company name: ");//prompting user for new employee's company name
					scanf("%s",oName);
					fflush(stdin);
					printf("Please enter the new employee\'s salary: ");//prompting user for new employee's salary
					scanf("%lf",&oSalary);
					updateFile(&start,pName,pAge,oId,oName,oSalary);// calling update file function , passing start pointer, employeee name, age, department id , company name and salary 
					break;
			case 7 :printf("Goodbye!");
					exit=1;//exit condition met
					break;
			default	:printf("Invalid input\n");
					break;//for invalid inputs
		}
	}
	
	return 0;
}

//Functions
void readFile(EMPLOYEETagPtr *start)//function to read from .txt file
{
	*start=NULL;//initializing start pointer to NULL
	FILE *fp;//creating a file pointer
	fp = fopen("employee.txt", "r");//opening the text file in read mode
	
	//read the data from the texfile into temprory variables
	fscanf(fp, "%s %d %d %s %lf", pName, &pAge, &oId, oName, &oSalary);
	//inserting the data into nodes
	while(!feof(fp))
	{
		//passing the values to the node
		insert(start,pName,pAge,oId,oName,oSalary);
		//reading the next line
		fscanf(fp, "%s %d %d %s %lf", pName, &pAge, &oId, oName, &oSalary);
	}
	fclose(fp);//closing the file
}


void insert(EMPLOYEETagPtr *start, char pName[], int pAge, int oId, char oName[], double oSalary)//inserting data into nodes
{
	EMPLOYEETagPtr newPtr = (EMPLOYEETagPtr)malloc(sizeof(EMPLOYEETag));//memory allocation for nodes
	strcpy(newPtr->personalInfo.name, pName);//using string copy to copy from temprory variable to node data
	newPtr->personalInfo.age = pAge;//directly assigning from temprory variables to node
	newPtr->officialInfo.deptId = oId;
	strcpy(newPtr->officialInfo.cmpName, oName);
	newPtr->officialInfo.salary = oSalary;
	newPtr->next = NULL;// assinging null to next

	EMPLOYEETagPtr previous = NULL;//initiating previous pointer to null
	EMPLOYEETagPtr current = *start;//initiating current pointer to start
	
	while (current != NULL && (strcmp( newPtr->personalInfo.name , current->personalInfo.name)>0))//searching for the position of the current pointer when sorted alphabetically
	{
		previous = current;
        current = current->next;
    }
	if(previous==NULL)
	{
		newPtr->next= *start;
		*start = newPtr;
		
	}
	else
	{
		newPtr->next = current;
		previous->next=newPtr;
	}
}

void displayEmployees(EMPLOYEETagPtr start)//to print the linked list
{
	EMPLOYEETagPtr current=start;//initiating  current pointer to start
	printf("\nName Age id Company Salary\n");//to make the displayed data meaningfull
	while(current != NULL)
	{
		printf("%s ", current->personalInfo.name);
		printf("%d ", current->personalInfo.age);
		printf("%d ", current->officialInfo.deptId);
		printf("%s ", current->officialInfo.cmpName);
		printf("%.2lf\n ", current->officialInfo.salary);
		current=current->next;//moving to next node
	}
}

int menu()//to display the menu
{
	int option;//using option to store the selected option
	printf("\n\nWelcome! This program reads the employee list from a text file and performs the below Operations.\n");
	printf("1. Display employee\'s details\n");
	printf("2. Search for an employee\'s salary\n");
	printf("3. Find the details of employee with the largest salary\n");
	printf("4. Find the details of all employees having salary less than 5000\n");
	printf("5. Find the average salary of a company \n");
	printf("6. Add new employee to the record\n");
	printf("7. Quit program\n");
	printf("Choose an option form the above to proceed: ");
	scanf("%d", &option);// allowing the user to select one and returns this option to the calling main()function
	return option;
	
}

void searchEmployee(EMPLOYEETagPtr start, char pName[])//to search for an employee
{
	int flag;//to validate input
	EMPLOYEETagPtr current=start;//initiating  current pointer to start

	while(current != NULL)//the loop ends when current is assigned NULL through current=current->next
	{
		if(strcmp(pName, current->personalInfo.name)==0)//comparing name to find the relavant node
		{
			printf("Name Age id Company Salary\n");
			printf("%s ", current->personalInfo.name);
			printf("%d ",current->personalInfo.age);
			printf("%d ", current->officialInfo.deptId );
			printf("%s ",current->officialInfo.cmpName);
			printf("%.2lf\n ",current->officialInfo.salary);
			flag = 1;//changing flag status
			break;
		}
		else
			current=current->next;
	}
	if (flag!=1)
		printf("Invalid Employee");//if entered name doesn't exist
}
	
void findMaximum(EMPLOYEETagPtr start)//find the employee with the highest salary
{
	EMPLOYEETagPtr current = start;//initiating  current pointer to start
	double max = 0;//to hold the maximum salary value
	EMPLOYEETagPtr maxSalaryEmployee = current;// initialiying pointer to point to employee with maximum salary
	while(current!=NULL)
	{
		if(current->officialInfo.salary > max)//current nodes salary comparison with the max
		{
			max = current->officialInfo.salary;//allocates the current highest salary value to max
			maxSalaryEmployee = current;//updates pointer to point to the current highest salary employee
		}
		current=current->next;//traversing
	}	
	printf("Name Age id Company Salary\n");
	printf("%s ",maxSalaryEmployee->personalInfo.name);
	printf("%d ",maxSalaryEmployee->personalInfo.age);
	printf("%d ",maxSalaryEmployee->officialInfo.deptId );
	printf("%s ",maxSalaryEmployee->officialInfo.cmpName);
	printf("%.2lf\n\n ",maxSalaryEmployee->officialInfo.salary);

}

void lowerSalary(EMPLOYEETagPtr start)//to find the employees with salaries less than 5000
{
	EMPLOYEETagPtr current = start;//initiating  current pointer to start
	double min = 5000.00;//the minimum salary to compare with 
	EMPLOYEETagPtr minSalaryEmployee = current;// initializing pointer that oints to employees with salaries lower than 5000 to current
	while(current!=NULL)
	{
		if(current->officialInfo.salary < min)//comparison with 5000
		{
			minSalaryEmployee = current;//assigning current node to minSalaryEmployee pointer to print
			printf("Name Age id Company Salary\n");
			printf("%s ",minSalaryEmployee->personalInfo.name);
			printf("%d ",minSalaryEmployee->personalInfo.age);
			printf("%d ",minSalaryEmployee->officialInfo.deptId );
			printf("%s ",minSalaryEmployee->officialInfo.cmpName);
			printf("%.2lf\n",minSalaryEmployee->officialInfo.salary);
		}
		current=current->next;//traversing to next node
	}
	printf("\n"); 
}

void averageSalary(EMPLOYEETagPtr start, char oName[])//to find the average salary of an employee at a given company
{
	int count=0;// to hold count of the number of employees
	double average=0;// to hold average value
	double total=0;// total salary eared by employees of the company
	EMPLOYEETagPtr current=start;//initiating  current pointer to start

	if(strcmp(oName,current->officialInfo.cmpName)==0)//validating the company name
	{
		while(current!=NULL)
		{
			total=total+(current->officialInfo.salary);//total calculation
			current=current->next;//traverse to next node
			count++;//increasing count per employee 
		}
		average=total/count;//average calculation
		printf("Average salary of an employee at %s is %.2lf\n", oName, average);
	}
	else
		printf("Invalid company\n");
	
}

void updateFile(EMPLOYEETagPtr *start, char pName[], int pAge, int oId, char oName[], double oSalary)//adding a new employee to the .txt file
{
	FILE *fp;//creating a file pointer
	fp = fopen("employee.txt", "a");//opening the file in append mode
	fprintf(fp, "\n%s %d %d %s %.2f\n", pName, pAge, oId, oName, oSalary);//Writing the new employee's details to the .txt file
	fclose(fp);//closing file 
	

	readFile(start);//reading the amemded .txt file 

	displayEmployees(*start);// printing the linked list
	
}



