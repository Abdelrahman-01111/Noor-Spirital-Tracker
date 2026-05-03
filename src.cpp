// NEW MEDHATT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<fstream>
#include<Windows.h>
#include <conio.h>
#include<string>
#include <vector>
#include<cstdlib>
#include<ctime>
#include<sstream>
#include<iomanip>


using namespace std;
#define RESET     "\033[0m"

#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define MAGENTA   "\033[35m"
#define CYAN      "\033[36m"
#define WHITE     "\033[37m"
#define GRAY      "\033[90m"
#define PURPLE "\u001b[35m"

//***********************************************************************************************
//تعليمات عشان يتحفظ اللي ات عاملته لازم تختار سته وعمل لوج اوت عشان يقفل المنيو و الحاجه اللي وراها تتشغل
//**********************************************************************************

string hadiths[] = { "عن النبي صلى الله عليه وسلم قال أفضل الأعمال أو العمل الصلاة لوقتها وبر الوالدين",
	" قال رسول الله صلى الله عليه وسلم أفضل الأعمال الحب فى الله والبغض فى الله",
	"عن معاذ بن جبل قال سألت رسول الله صلى الله عليه وسلم أي الأعمال أحب إلى الله قال أن تموت ولسانك رطب من ذكر الله",
	"قال صلى الله عليه وسلم من قام رمضان إيمانا واحتسابا غفر له ما تقدم من ذنبه ",
	"قال صلى الله عليه وسلم من قام مع إمامه حتى ينصرف كتب له قيام ليلة",
	"قال صلى الله عليه وسلم أفضل الصدقة صدقة في رمضان ",
	"قال صلى الله عليه وسلم من فطر صائما كان له مثل أجره غير أنه لا ينقص من أجر الصائم شيء ",
	"عن النبي صلى الله عليه وسلم أنه قال من صلى الفجر في جماعة ثم قعد يذكر الله حتى تطلع الشمس ثم صلى ركعتين كانت له كأجر حجة وعمرة تامة تامة تامة",
	"المسلم من سلم المسلمون من لسانه ويده والمهاجر من هجر ما نهى الله عنه",
	"يقول الرسول صلي الله عليه وسلم الصلوات الخمس والجمعة إلى الجمعة ورمضان إلى رمضان كفارات لما بينهن ما لم تغش الكبائر" };
string zagrapha = R"(╔══════════════════════════════════════╗
║          In The Name Of Allah        ║
║       🌙  Hadeeth Of Day  📜         ║
║                                      ║
╚══════════════════════════════════════╝
)";



//******************************************************************************************
//******************************************************************************************


struct Time {
	int hour;
	int minutes;
};

struct prayers {
	Time fajr, sunrise, dhuhr, asr, maghrib, isha;
};







//*****************************************************************************************
struct user {
	int userid;
	string username;
	string password;
	int currentjuz;
	int dailygoal;
	int prayer_tracker[30][5];//we will show in the calendar
};
user users[15] = {};

int currentuser;//ملفات




//********************************************************************************************
//********************************************************************************************

struct Athkar {
	int thikrID;
	string content;
	string category;
	int targetRepetition;
};

Athkar myLibrary[100] = {
	// Morning
	{1, "أصبحنا و أصبح الملك لله رب العالمين", "Morning", 1},
	{2, "بسم الله اللذي لا يضر مع إسمه شيء في الأرض ولا في المساء وهو السميع العليم", "Morning", 3},
	{3, "اللهم بك أصبحنا و بك أمسينا و بك نحيا و بك نموت و إليك النشور", "Morning", 3},
	// Evening
	{4, "اللهم إني أمسيت أشهدك وأشهد حملة عرشك وملائكتك وجميع خلقك أنك أنت الله لا إله إلا أنت وحدك لا شريك لك وأن محمد عبدك و رسولك", "Evening", 4},
	{5, "اللهم ما أمسي بي من نعمة أو يأخذ من خلقك فمنك وحدك لا شريك لك فلك الحمد ولك الشكر", "Evening", 3},
	{6, "اللهم بك أمسينا و بك أصبحنا و بك نحيا و بك نموت و إليك المصير", "Evening", 1},
	// After Prayer
	{7, "لا إله إلا الله وحده لا شريك له له الملك و له الحمد يحيي و يميت وهو علي كل شيء قدير", "After Prayer", 10},
	{8, "اللهم أجرني من النار", "After Prayer", 7},
	{9, "اللهم اعني علي ذكرك و شكرك و حسن عبادتك ", "After Prayer", 3},
	// Before Sleep
	{10, "باسمك ربي وضعت جنبي وبك أرفعه فإن أمسكت نفسي فارحمها و إن ارسلتها فاحفظها بما تحفظ به عبادك الصالحين", "Before Sleep", 3},
	{11, "اللهم إنك خلقت نفسي وأنت توفاها لك مماتها و محياها فاحفظها وإن أمتها فاغفر لها اللهم إني أسألك العافية", "Before Sleep", 3},
	{12, "اللهم قني عذابك يوم تبعث عبادك", "Before Sleep", 3}
};






/// *********************************************************************************************************************
//**********************************************************************************************************************

struct daily_progress {

	int log_id;
	int user_id;
	int ramadan_day;
	int tasabeeh_counter;
	int Quran_Juz;
	int points = 0;
	bool Five_prayers[5];
	bool Bonus_prayers[2];
	bool daily_goal;
};

struct reports
{
	int total_prayers = 0;
	int total_tasbeeh = 0;
	int total_goals_achieved = 0;
	int total_bonus_prayers = 0;
	int latest_day = 0;
	int total_points = 0;
	string rank;
};



reports reps[10];
daily_progress logs[10];
int logid = 0;


int savedid;//عشان نعرف مين اللي فاتح دلوقتي//new

//*****************************************************************************************
//*****************************************************************************************



struct tasbeeha {
	int id;
	string T;
	int totalcount = 0;   //قيمه ابتدائيه لكله //new
};


tasbeeha tasabeeh[10] = {//غيرت الحجم عشان لو الادمن هيضيف تاني
	{ 1, "Subhan_Allah", 0 },
	{ 2, "Alhamdu_lillah", 0 },
	{ 3, "Allahu_Akbar", 0 },
	{ 4, "La_ilaha_illa_Allah", 0 }
};

int current_tasbeeha;//ملفات

int total_tasabeeh = 0;//عشان تروح للdaily prog






/////////////NASER
/*int new_index = 0;
int new_id = 0;
int last_id = 0;
//////////////////

void lastid(tasbeeha tasabeeh[], tasbeeha);
void input_tasabeeh(tasbeeha tasabeeh[]);
void add_tasbeeha(tasbeeha tasabeeh[]);
void display(tasbeeha tasabeeh[]);
void save_tasbeeh(tasbeeha tasabeeh[]);
*/


//************************************************************************************************
//*****************************************************************************************


void loadusers(user arr[]);
void saveusers(user arr[]);


void reverse_ar(string arrabic);//new
void print_ar(string arrabic);//new




void authmenu();
void login();
void signup();
void getpassword(string&);


void mainmenu();//new
void adminmenu();//new

void loadtasabeeh(tasbeeha arr[]);//new
void savetasabeeh(tasbeeha arr[]);//new

void save_reps();
void load_reps();

void save_daily_progress(daily_progress arr[], int count);//Hi
void load_daily_progress(daily_progress arr[], int& count);//Hi

void tasbeehcount(int index);//new
void showalltasabeeh();//new
int Today_tasabeeh();//new
void Editing_tasabeeh();//تنظيم


void upd_daily_prog();
void upd_reports(daily_progress& d1, daily_progress const& d2 = { 0, 0, 0, 0, 0, 0, { 0,0,0,0,0 }, { 0,0 }, 0 });
void show_reports();
void edit_logs();


void hadith_of_day();//new
int check_valid_number(int min_value, int max_value);//fahl
void search_for_day(int day_Number);//fahl
void add_minute(int& hour, int& minute);//fahl
void generate_full_calendar();//fahl
void modify_calender(int day, string target_prayer, string new_time);//fahl
void Special_EVENT(int special_day);//fahl
void Editing_and_Show_calendar();//تنظيم
void Show_Calendar();//تنظيم


void saveAthkarToFile(Athkar library[], int size);//
void loadAthkarFromFile(Athkar library[], int& size);//
void adminModuleAthkar(Athkar library[], int& size);//
void runAthkarModule(Athkar library[], int size, string selectedCategory);//

void show_athkar();//new

int currentSize;// = 0;//ملوش لازمه لان كدا كدا بيتظبط ف اللود

void Add_new_tasbeeha();
void delete_tasbeeha();

void Editing_tasabeeh();
void display_for_admin();



//*****************************************************************************************
//****************************************************************************************************

int main() {

	SetConsoleOutputCP(65001); // لضبط الإخراج (Output)
	SetConsoleCP(65001);       // لضبط الإدخال (Input) لو هتعمل cin لعربي
	srand(time(0));

	load_reps();
	loadtasabeeh(tasabeeh);
	loadusers(users);
	load_daily_progress(logs, logid); //Hi
	loadAthkarFromFile(myLibrary, currentSize);


	users[0] = { 0,"admin","1111",0,0 };
	users[1] = { 1,"adel","1234",1,100 };
	users[2] = { 2,"medhat","1122",1,220 };

	authmenu();


	system("pause");
}

//****************************************************************************************************
int Today_tasabeeh() {



	for (int i = 0; i < current_tasbeeha; i++) {

		if (tasabeeh[i].totalcount > 0)
		{
			cout << "\n \n" << tasabeeh[i].T << ":" << tasabeeh[i].totalcount << endl;
		}

	}
	cout << "\n──────────────────────\n";
	cout << BLUE "Total Tasbeeh: " << total_tasabeeh << RESET << endl;
	cout << "──────────────────────\n";


	return 0;// total;//هنعمل ريترن للتوتال كله مش لتسبيحه معينه
}

//****************************************************************************************************



void tasbeehcount(int index) {
	system("cls");
	int counter = 0;

	cout << "Press any key to count (Press 'q' to save and exit)\n";
	cout << "--------------------------------------------------\n";

	while (true) {
		char ch = _getch();

		if (ch == 'q' || ch == 'Q') {
			break;
		}

		counter++;

		cout << "\rCurrent Count: " << counter << "   " << flush;

	}
	tasabeeh[index].totalcount += counter;
	total_tasabeeh += counter;//تعديل
	Today_tasabeeh();

	cout << "\n \n " << GREEN << "Press Any Key To Return Mainmenu..." << RESET << endl;

	char c = _getch();//منغيرها مش بنلحق نشوف الداله اللي فوقيها
	//system("pause");//لو في داله عرض
}



//****************************************************************************************************
//****************************************************************************************************


void showalltasabeeh() {

	system("cls");

	cout << YELLOW << " \t \t \t \tPlease Enter the ID Of Tasbeeha \n \n" << RESET;

	for (int i = 0; i < current_tasbeeha; i++) {

		cout << tasabeeh[i].id << "." << tasabeeh[i].T << "\n \n";

	}

	char c = _getch();
	int choice = c - '0';
	choice--;
	int index = choice;
	//المستخدم بيختار رقمه ظاهر ليه علي الشاشه الايندكس اقل من الرقم ده بواحد

	if (-1 < index && index < current_tasbeeha)

	{
		tasbeehcount(index);
	}

	else

	{
		//cout << "Please Enter Correct ID\n";
		showalltasabeeh();
	}


}


//****************************************************************************************************
//****************************************************************************************************
bool isadmin = 0; //تعديل الفحل عشان نقدر كلنا نستخدمه 

void adminmenu() {
	//bool runing = 1;
	while (true)
	{
		system("cls");
		cout << GREEN << "Hello Admin You Can Add OR Delet Any Thikr OR Tasbeeha & Manage Calendar \n \n" << RESET;

		cout << "1.Add Or delete Zikr \n \n" <<
			"2.Add Or delete Tasabeeh \n \n" <<
			"3.Manage Calendar \n \n" <<
			"4.Log Out To Save \n \n";
		char c = _getch();

		if (c == '1') {
			adminModuleAthkar(myLibrary, currentSize);
		}

		else if (c == '2') {
			Editing_tasabeeh();
		}
		else if (c == '3') {
			Editing_and_Show_calendar();
		}

		else if (c == '4')
			exit(0);//يخرج خالص
	}


}





//****************************************************************************************************
//****************************************************************************************************


void mainmenu() {
	//bool runing = 1;

	while (true)
	{
		system("cls");//عشان لما يجي يرجع لل مين منيو يمسح كل اللي كان علي الشاشه
		cout << PURPLE << "\t \t \t   It's time to achive your goals! 🌙\n\n" << RESET;
		cout << YELLOW << "\t \t \t \t Choose an Option <1-7>: \n \n" << RESET;
		cout <<
			"1.View Athkar Library \n \n" <<//omar
			"2.Digital Tasbeeh \n \n" <<//emad
			"3.Update Daily Progress \n \n" <<//reda
			"4.Show My Reports \n \n" <<//reda
			"5.Calendar \n \n" <<//ahmed
			"6.Edit Logs\n \n" <<//reda
			"7.Log Out To Save  \n \n";


		char c = _getch();

		if (c == '1') {
			show_athkar();
		}


		else if (c == '2') {

			showalltasabeeh();
		}
		else if (c == '3') {

			upd_daily_prog();
		}
		else if (c == '4')
		{
			show_reports();
		}
		else if (c == '5') {

			Show_Calendar();
		}

		else if (c == '6')
		{
			edit_logs();
		}

		else if (c == '7')
		{

			exit(0);//عايزه يقفل فورا 
		}


	}//قفله اللوب 


}






//****************************************************************************************************
//****************************************************************************************************





void signup()
{

	system("cls");

	cout << " ======================\n";
	cout << YELLOW << "|  Create An Account 🌙 |\n" << RESET;
	cout << " ======================\n\n";

	string username, password = "";
	int currentjuz, dailygoal;
	cout << "Username: ";

	getline(cin, username); //to prevent user from typing space in uname becuz crashes the app 
	while (username.find(' ') != -1) {

		cout << RED << "Username can not contain spaces" << RESET << endl;
		cout << "Username: ";
		getline(cin, username);
	}
	
	for (int i = 0; i < currentuser; i++) {// check if username already exisits 
		if (username == users[i].username) {
			cout << RED << "This Username is Already Used :(\n\n" << RESET;
			cout << YELLOW << "[X] " << RESET << "Log in instead?\n";
			cout << BLUE << "[Any Key] " << RESET << "Try Again\n";
			char c = _getch();
			if (c == 'x' || c == 'X') {
				login();

			}
			else {
				signup();

			}
			return; // عشان ميكملش في الفنكشن بعد ما تحصل مشكلة اليوزرنيم
		}
	}

	bool confirmpass = 0;
	while (password.size() < 4 || !confirmpass) {
		password = "";
		cout << "Password (👀 <tab>):  ";
		getpassword(password);
		if (password.size() < 4) {
			cout << endl << RED << "Password should be at least 4 characters";
			cout << RESET;
		}
		else {
			string pass2 = "";
			cout << "\nComfirm Password  (👀 <tab>): ";
			getpassword(pass2);
			if (pass2 == password) {
				confirmpass = 1;
			}
			else {

				cout << endl << RED << "Passwords don't Match 😭" << RESET;
			}
		}

		cout << endl;

	}
	cout << "What juz are you currently in? : ";

	currentjuz = check_valid_number(1, 30);


	cout << "Daily Reading  Goal: ";
	cin >> dailygoal;
	cin.ignore(10000, '\n');
	if (cin.fail()) {
		// if user enters a wrong type like char 

		cin.clear();
		cin.ignore();
		cout << RED << "Enter a number, please" << RESET << endl;

		cout << "Daily Reading  Goal: ";
		cin >> dailygoal;
	}


	users[currentuser] = { currentuser,username,password,currentjuz, dailygoal };
	savedid = users[currentuser].userid;//new     عشان نعرف مين فاتح دلوقتي

	//الترتيب مهم احنا عايزين نحفظ للراجل ده مكانه ف الفايل قبل ما نفتح المنيو لان كل
	//دا مش هيتسجل معانا غير لما المنيو تقفل وهي مش هتقفل الا لما تدوس سته

	saveusers(users);//بحفظله مكانه الاول
	//currentuser++;//مش عارف هو كدا كدا مش هيعمل ساين اب مرتين لازم يقفل ويفتح اللود وساعتها هيحصل زياده للعداد
	hadith_of_day();
	char c = _getch();//مكناش بنلحق نشوف الحديث
	mainmenu();//new


}




//****************************************************************************************************
//****************************************************************************************************





void login() {
	system("cls");
	cout << " ===========\n";
	cout << YELLOW << "|  Log in 👋 |\n" << RESET;
	cout << " ===========\n\n";
	string username, password;
	cout << "Username: ";
	cin >> username;
	cin.ignore(10000, '\n');
	cout << "Password (👀 <tab>):  ";
	getpassword(password);



	if (username == "admin" && password == "1111") {
		isadmin = 1;
		adminmenu();
		return;//عشان لما يرجع هنا هيكمل باقي الداله واحنا مش عايزين كدا
	}




	for (int i = 0; i < currentuser; i++) {
		if (username == users[i].username && password == users[i].password) {
			savedid = users[i].userid;//new عشان نعرف مين فاتح دلوقتي
			hadith_of_day();
			_getch();//مكناش بنلحق نشوف الحديث
			mainmenu();
			return;
		}
	}
	cout << endl << RED << "Wrong Username or Password!\n\n\n" << RESET;
	cout << YELLOW << "[X] " << RESET << "Go Back\n";
	cout << BLUE << "[Any Key] " << RESET << "Try Again\n";
	char c = _getch();
	if (c == 'x' || c == 'X') {
		authmenu();
	}
	else {
		login();
	}
}
void getpassword(string& password) {
	char c = '0';
	bool show = 0;
	while (1) {
		c = _getch();
		if (c == char(8)) {// backspace
			if (password == "")continue;//اكيد مش هنمسح ولا حاجه
			cout << "\b \b"; //delete last char on terminal
			password.erase(password.size() - 1);// delete last char on password
			continue;
		}
		else if (c == '\t') { //show/hide password with tab 
			for (int i = password.size(); i--;) {
				cout << "\b \b";// delete chars or stars
			}
			if (show) {
				string s(password.size(), '*');
				cout << s;
				show = 0;
			}
			else {
				cout << password;
				show = 1;
			}
		}
		else if (c == ' ') {// prevent spaces on passwords
			continue;
		}
		else if (c == char(13)) { //break when press enter
			break;
		}
		else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '@' || c == '$' || c == '#') {
			//it accepts only numbers, litters, and some symbols but no special keys like (arrows) 
			if (show) cout << c; else cout << '*';
			password += c;
		}
	}

}







//****************************************************************************************************
//****************************************************************************************************




void authmenu() {
	system("cls");
	cout << " =====================\n";
	cout << YELLOW << "|  Welcome to Noor ✨ |\n" << RESET;
	cout << " =====================\n\n";
	cout << "[S] Sign Up" << "\n";
	cout << "[L] Log In" << "\n";
	char c = _getch();
	if (c == 'S' || c == 's') {
		signup();
	}
	else if (c == 'L' || c == 'l') {
		login();
	}
	else {
		authmenu();
	}
}

//****************************************************************************************************
//****************************************************************************************************



void loadusers(user arr[]) {
	//currentuser = 0;
	ifstream inputusers("users.txt");

	if (inputusers.is_open())
	{

		if (inputusers.peek() == EOF) { currentuser = 3; }//بتشوف لو اول حرف هو اخر الملف يبقي فاضي وكمان مش لازم تقفل الملف فوق هو كدا كدا هينزل تحت ويقفل
		else currentuser = 0;

		// inputusers.close();}//عايزين و الملف فاضي العداد يبقي بتلاتع غير كدا يبقيي بصفر وهو كدا كدا هيزيد لما يخش جوا الداله



		while (inputusers >> arr[currentuser].userid >>
			arr[currentuser].username >>
			arr[currentuser].password >>
			arr[currentuser].currentjuz >>
			arr[currentuser].dailygoal)//ده شرط مفيش;
		{
			currentuser++;
		}

		inputusers.close();
	}
	else cout << "ERROR IN LOADING USER FILE";
}

//****************************************************************************************************
//****************************************************************************************************







void saveusers(user arr[]) {

	ofstream outputusers;
	outputusers.open("users.txt");

	if (outputusers.is_open() == true)
	{
		for (int i = 0; i <= currentuser; i++)
		{
			outputusers << arr[i].userid << " " <<
				arr[i].username << " " <<
				arr[i].password << " " <<
				arr[i].currentjuz << " " <<
				arr[i].dailygoal << endl;
		}
		outputusers.close();
	}
	else cout << "ERROR IN SAVING USER FILE";
}


//**********************************************************************************************
//**********************************************************************************************


void loadtasabeeh(tasbeeha arr[]) {
	ifstream input("tasabeeh.txt");

	if (input.peek() == EOF)current_tasbeeha = 4;//لو الملف فاضي السيف هتشتغل واخرها اربعه عشان تكتب الاربع تسبيحات 
	else current_tasbeeha = 0;

	string line;
	while (getline(input, line))//كدا احنا بنقرا اول حاجه اللي هي الايدي 
		//فلما نيجي نقسم بتبوظ
		//لازم نقرا السطر كله ثمم نقسمه
	{
		stringstream ss(line);
		ss >> arr[current_tasbeeha].id >> arr[current_tasbeeha].T;
		current_tasbeeha++;
	}
	input.close();

}

//**********************************************************************************************
//**********************************************************************************************


void savetasabeeh(tasbeeha arr[]) {
	ofstream output("tasabeeh.txt");
	for (int i = 0; i < current_tasbeeha; i++) {//كان فيه =

		output << arr[i].id << " " << arr[i].T << endl;


	}


	output.close();

}

//**********************************************************************************************
//**********************************************************************************************

void load_daily_progress(daily_progress arr[], int& count) {
	count = 0;
	ifstream input("daily_progress.txt");

	if (!input.is_open()) {
		// لو الفايل مش موجود مش هيحصل ايرور بس
		return;
	}
	//  نفس الكلام بس لو فاضي
	if (input.peek() == EOF) {
		input.close();
		return;
	}
	string header;
	getline(input, header);

	while (input >> arr[count].log_id
		>> arr[count].user_id
		>> arr[count].ramadan_day
		>> arr[count].tasabeeh_counter
		>> arr[count].Quran_Juz
		>> arr[count].points
		>> arr[count].Five_prayers[0]
		>> arr[count].Five_prayers[1]
		>> arr[count].Five_prayers[2]
		>> arr[count].Five_prayers[3]
		>> arr[count].Five_prayers[4]
		>> arr[count].Bonus_prayers[0]
		>> arr[count].Bonus_prayers[1]
		>> arr[count].daily_goal)
	{
		count++;
	}

	input.close();
}

//**********************************************************************************************
//**********************************************************************************************

void save_daily_progress(daily_progress arr[], int count) {
	ofstream output("daily_progress.txt");

	if (output.is_open()) {
		output << "LogID  UserID  Day  tasabeeh  Juz  Points  Fajr  Dhuhr  Asr  Maghrib  Isha  Taraweeh  Tahajud  Goal " << endl;
		for (int i = 0; i < count; i++) {
			output << arr[i].log_id << "      "
				<< arr[i].user_id << "       "
				<< arr[i].ramadan_day << "    "
				<< arr[i].tasabeeh_counter << "         "
				<< arr[i].Quran_Juz << "    "
				<< arr[i].points << "     "
				<< arr[i].Five_prayers[0] << "     "
				<< arr[i].Five_prayers[1] << "      "
				<< arr[i].Five_prayers[2] << "    "
				<< arr[i].Five_prayers[3] << "        "
				<< arr[i].Five_prayers[4] << "     "
				<< arr[i].Bonus_prayers[0] << "         "
				<< arr[i].Bonus_prayers[1] << "        "
				<< arr[i].daily_goal
				<< endl;
		}
		output.close();
		cout << GREEN << "Daily progress saved successfully!\n" << RESET;
	}
	else {
		cout << RED << "ERROR: Could not save daily progress file\n" << RESET;
	}
}




//**********************************************************************************************
//**********************************************************************************************

void save_reps() {
	ofstream output("reda.txt");
	if (output.is_open()) {
		output << "UserId \t latest_day \t total_tasbeeh \t  total_goals \t total_prayers \t total_bonus_pra \t total_points" << endl;
		for (int i = 0; i < 10; i++) {

			output << i << " \t  \t"
				<< reps[i].latest_day << "     \t \t "
				<< reps[i].total_tasbeeh << "   \t \t "
				<< reps[i].total_goals_achieved << "  \t  \t"
				<< reps[i].total_prayers << " \t  \t "
				<< reps[i].total_bonus_prayers << "  \t  \t  \t"
				<< reps[i].total_points << endl;
		}
		output.close();
	}
}

//**********************************************************************************************
//**********************************************************************************************

void load_reps() {
	ifstream input("reda.txt");
	if (input.is_open()) {
		string header;//اني
		getline(input, header);//اني
		int id;
		// بنصفر عشان نبقي علي نضافه عشان دي السجلات
		for (int i = 0; i < 10; i++) reps[i] = { 0,0,0,0,0,0 };

		while (input >> id) {
			input >> reps[id].latest_day
				>> reps[id].total_tasbeeh
				>> reps[id].total_goals_achieved
				>> reps[id].total_prayers
				>> reps[id].total_bonus_prayers
				>> reps[id].total_points;
		}
		input.close();
	}
}

//**********************************************************************************************
//**********************************************************************************************


void upd_daily_prog()
{

	// /لما نستدعي الداله هي اللي هتروح تجيب التوتال بنفسها
	//لان اللي بيستدعي الداله هو لسه ميعرفش مجموع تسبيحاته اي

	char e;
	system("cls");
	cout << YELLOW << "DO you want to update your daily progress?\n\n" << CYAN << "[U] " << RESET << "Update Progress\n\n" << CYAN << "[Any Key] " << RESET << "Return To Main Menu";
	e = _getch();
	if (e != 'u' && e != 'U')
	{
		mainmenu();
	}
	else if (e == 'u' || e == 'U')
	{
		system("cls");
		cout << CYAN << "Your ID is " << savedid << endl;
		logs[logid].points = 0;
		logs[logid].tasabeeh_counter = total_tasabeeh;		// بنحلي النقاط في البداية بصفر و بنزود التسبيح اللي عمله و بنخلي اليوزر أيدي بيساوي الأيدي بتاعه و بنزود التسابح على النقاط
		logs[logid].user_id = savedid;
		logs[logid].points += total_tasabeeh;

		int check;
		char e;
		int counter = 0; // بنستعمله في تسجيل الايام عشان نسجل الأراي بالترتيب
		string prayers[7] = { "Fajr", "Dhuhr", "Asr", "Maghrib", "Isha", "Taraweeh", "Tahajud" };
		int used_days[10] = {}; // بنسجل الأيام المستعملة عشان ميدخلهاش تاي ممكن يروح يعدلها
		bool used_day = false; // بنستعملها عشان نعرف اليوم اللي دخله موجود وقديم ولا لأ
		for (int i = 0; i < 10; i++)
		{
			if (logs[i].user_id == savedid)
			{
				used_days[counter] = logs[i].ramadan_day; // بنسجل كل الأيام السابقة اللي موجودة اللي سجلها عشان ميدخلهاش تاني 
				counter++;
			}
		}

		cout << RESET << "Which day of ramadan? ";
		check = check_valid_number(1, 30);

		for (int i = 0; i < 10; i++)
		{
			if (check == used_days[i])
			{
				used_day = true;
			}
			// هنا بنشوف اليوم اللي دخله كان موجود قبل كدة ولا لأ لو موجود بنمنعه يدخله تاني ممكن يروح يعدله في دالة التعديل
			if (used_day == true)
			{
				cout << RED << "\nThis day exists in a different log, Please re-enter:" << RESET << "\n\nWhich day of ramadan ?  ";
				check = check_valid_number(1, 30);
				i = -1;
				used_day = false;
			}
		}
		logs[logid].ramadan_day = int(check);

		cout << "\n( 1 => Yes, 0 => No )\n";

		for (int i = 0; i < 5; i++) // بنسأله عن الصلوات الحمسة			
		{
			cout << "\nDid you pray " << prayers[i] << "?[" << GREEN
				<< "1" << RESET << " / " << RED << "0" << RESET << "] " << " ("
				<< GREEN << "+10 Pts" << RESET << " / " << RED << "-5 Pts" << RESET << ") ";

			check = check_valid_number(0, 1);
			logs[logid].Five_prayers[i] = check;

			if (logs[logid].Five_prayers[i] == 1)
			{
				logs[logid].points += 10;
			}
			else if (logs[logid].Five_prayers[i] == 0)	//  بنزود نقاط على الصلاة لو صلاها يزيد 10 لو لأ ينقص 5
			{
				logs[logid].points -= 5;
			}
		}

		if (logs[logid].ramadan_day != 30)
		{
			for (int i = 5; i < 7; i++) // Bonus Prayers
			{
				cout << YELLOW << "\n[BONUS]" << RESET << " Did you pray " << prayers[i] << "?[" << GREEN
					<< "1" << RESET << " / " << RED << "0" << RESET << "] " << " ("
					<< GREEN << "+15 Pts" << RESET << " / " << RESET << "-) ";											//نفس الكلام بس ديه صلوات BONUS
				check = check_valid_number(0, 1);
				logs[logid].Bonus_prayers[i - 5] = check;

				if (logs[logid].Bonus_prayers[i - 5] == 1)
				{
					logs[logid].points += 15;
				}

			}
		}

		cout << "\nHave you achieved your daily goal? " << "[" << GREEN
			<< "1" << RESET << " / " << RED << "0" << RESET << "] " << " ("
			<< GREEN << "+20 Pts" << RESET << " / " << RED << "-10 Pts" << RESET << ") ";

		check = check_valid_number(0, 1);
		logs[logid].daily_goal = check;
		if (logs[logid].daily_goal == 1)
		{																						//  بنسأله عن هدفه اليومي حققه ولا لأ وبنجطله النقاط
			logs[logid].points += 20;
		}
		else if (logs[logid].daily_goal == 0)
		{
			logs[logid].points -= 10;
		}

		cout << "\nWhich juz of The Quarn have you reached? ";
		check = check_valid_number(0, 30);									// بنسأله عن جزء القرآن 0 معناها مبدأش
		logs[logid].Quran_Juz = int(check);

		cout << YELLOW << "\n\nWould you like to change your answers?\n\n" << CYAN << "[E] " << RESET << "Edit Answers\n\n" << CYAN << "[Any Key] " << RESET << "Return To Main Menu";
		e = _getch();

		if (e == 'e' || e == 'E')
		{
			logs[logid].points = 0;
			logs[logid].ramadan_day = 0;
			upd_daily_prog();								// هنا بنسأله لو عايز يغير أجاباته أو يرجع للمنيو
		}
		else if (e != 'e' && e != 'E')
		{
			logs[logid].log_id = logid;		// لو قال يرجع للمنيو بنسجل اللوج أيدي في السجل و بنزوده واحد عشان اللي هيدخل الدالة بعديه
			logid++;
			upd_reports(logs[logid - 1]); // بنبعت السجل لدالة الابديت عشان تحدث التقارير و بنقلل من اللوج أيدي واحد عشان زودناه قبلها عشان نبعت اللوج أيدي بتاع السجل ده مظبوط
			mainmenu();
		}


	}
}
//***********************************************************************************/
void upd_reports(daily_progress& d1, daily_progress const& d2)
{
	int id = d1.user_id;

	if (d1.ramadan_day <= reps[id].latest_day && d2.ramadan_day != 0)
	{
		int new_day = 0;									// لو دخل يوم أقل من أخر يوم وفي نفس الوقت الباراميتر التاني مش فاضي ده معناه إنه جاي من دالة التعديل فهنعدل البيانات
		int prayers_cntr = 0;
		int bonus_prayers_cntr = 0;
		int goal_cntr = 0;

		for (int i = 0; i < 5; i++)
		{
			if (d1.Five_prayers[i] > d2.Five_prayers[i])
			{
				prayers_cntr--;
			}
			else if (d1.Five_prayers[i] < d2.Five_prayers[i])		// عملنا هنا عداد بيزيد و بيقل حسب هو غير الصلاة بتاعته ل ايه
			{
				prayers_cntr++;
			}
			else
			{
				continue;
			}

		}
		reps[id].total_points += prayers_cntr * 15;					// النقاط بنجمع عليها العداد ده في 15 يعني لو كان صلى بعدين عدلها خلاها مصلاش هيخسر ال 10 نقط بتوع الصلاة بعدين هينقص 5 نقط بتوع اللي مصلاش
		d1.points += prayers_cntr * 15;

		for (int i = 0; i < 2; i++)
		{
			if (d1.Bonus_prayers[i] > d2.Bonus_prayers[i])
			{
				bonus_prayers_cntr--;
			}
			else if (d1.Bonus_prayers[i] < d2.Bonus_prayers[i])			// عملنا هنا عداد بيزيد و بيقل حسب هو غير الصلاة البونص بتاعته ل ايه
			{
				bonus_prayers_cntr++;
			}
			else
			{
				continue;
			}
		}
		reps[id].total_points += bonus_prayers_cntr * 15;			// النقاط بنجمع عليها العداد ده يعني لو كان مصلاش بعدين عدلها و صلى هيكسب ال 15 نقطة بتوع الصلاة البونص 
		d1.points += bonus_prayers_cntr * 15;


		if (d1.daily_goal > d2.daily_goal)
		{
			goal_cntr--;
		}
		else if (d1.daily_goal < d2.daily_goal)						// عملنا هنا عداد بيزيد و بيقل حسب هو غير نتيجة الهدف اليومي بتاعته ل ايه
		{
			goal_cntr++;
		}
		reps[id].total_points += goal_cntr * 30;					// النقاط بنجمع عليها العداد ده يعني لو كان معملش الهدف اليومي بعدين عدلها خلاها عمله هنشيل من عليه ال10 نقاط اللي كان ناقصهم بعدين هنزود ال20 نقطة بتوع التحقيق 
		d1.points += goal_cntr * 30;


		reps[id].total_prayers += prayers_cntr;
		reps[id].total_bonus_prayers += bonus_prayers_cntr;			// بنجمع العدادات ديه على توتال الصلوات وكدة بحيث تزيد أو تقل
		reps[id].total_goals_achieved += goal_cntr;



		d1.ramadan_day = d2.ramadan_day;
		for (int i = 0; i < 5; i++)
		{
			d1.Five_prayers[i] = d2.Five_prayers[i];
		}
		for (int i = 0; i < 2; i++)
		{
			d1.Bonus_prayers[i] = d2.Bonus_prayers[i];
		}												// بنساوي الخانات اللي في السجل الأساسي باللي في التعديل عشان نسجلها في الفايلات ديلي بروجرس

		d1.daily_goal = d2.daily_goal;
		d1.Quran_Juz = d2.Quran_Juz;

		for (int i = 0; i < 10; i++)
		{
			if (logs[i].user_id == savedid)
			{
				if (logs[i].ramadan_day > new_day)
					new_day = logs[i].ramadan_day;		// بنمشي على كل السجلات بتاعته عشان نشوف أكبر يوم ونخليه latest day
			}
		}
		reps[id].latest_day = new_day;


	}


	else
	{
		if (d1.ramadan_day > reps[id].latest_day)		// لو هو مش جاي يعدل هيدخل هنا و هنشوف لو اليوم اللي بيدخله أكبر من أخر يوم متسجل هنخليه هو الأخير ولو بيسجل يوم قديم مش هيحصل حاجة
			reps[id].latest_day = d1.ramadan_day;

		reps[id].total_tasbeeh += d1.tasabeeh_counter; // بنزود توتال التسبيح

		if (d1.daily_goal == 1)
		{
			reps[id].total_goals_achieved++;	// بنزود توتال الأهداف المحققة
		}
		for (int i = 0; i < 5; i++)
		{
			if (d1.Five_prayers[i] == 1)
			{
				reps[id].total_prayers++;		// بنزود توتال الصلوات
			}
		}

		for (int i = 0; i < 2; i++)
		{
			if (d1.Bonus_prayers[i] == 1)
			{
				reps[id].total_bonus_prayers++;		// بنزود توتال الصلوات البونص
			}
		}

		reps[id].total_points += d1.points;
	}


	if (reps[id].total_points >= 5250)
		reps[id].rank = "🌟 Al-Muhsin";
	else if (reps[id].total_points >= 4500)
		reps[id].rank = "💎 Al-Muttaqi";
	else if (reps[id].total_points >= 3750)
		reps[id].rank = "🥇 Al-Mukhlis";
	else if (reps[id].total_points >= 3000)			// بنحدد الرانك بتاعه
		reps[id].rank = "🥈 Al-Mujtahid";
	else if (reps[id].total_points >= 2250)
		reps[id].rank = "🥉 Al-Multazim";
	else if (reps[id].total_points >= 1500)
		reps[id].rank = "🌱 Al-Muwazib";
	else if (reps[id].total_points >= 750)
		reps[id].rank = "⚠️ Al-Muhawil";
	else
		reps[id].rank = "🛑 Al-Muqassir";

	save_daily_progress(logs, (logid)); // في أخر كل دالة ابديت بنحفظ الديلي بروجرس سواء عدل أو دخل سجل جديد في فايل ديلي بروجرس
	save_reps(); //reda بنحفظ التقارير في فايل
}

//***********************************************************************************/

void show_reports()
{
	system("cls");
	int latest_day = reps[savedid].latest_day;
	int total_prayers = reps[savedid].total_prayers;
	int total_bonus_prayers = reps[savedid].total_bonus_prayers;		// عملنا متغيرات غشان نعرضها وساويناها باللي في التقارير من صلوات ونقطر و رانك وهكذا
	int total_tasbeeh = reps[savedid].total_tasbeeh;
	int total_goals_achieved = reps[savedid].total_goals_achieved;
	int total_points = reps[savedid].total_points;
	string current_rank = reps[savedid].rank;
	int remain_pts;
	string next_color; // دول بنستعملهم عشان لما نيجي نعرض الرانك
	string next_rank;
	char ret; // بنستعمله في الرجوع للمنيو

	if (latest_day == 0)
	{
		cout << CYAN << "You haven't made any progress yet!\n";

		cout << RESET << "\nTo " << RED << "RETURN " << RESET << "press " << RED << "Any Key "; // لو أحدث يوم ليه ب صفر يبقى كدة معملش أي سجل
		ret = _getch();
		mainmenu();
	}

	else if (latest_day != 0)
	{

		cout << CYAN << "Your " << RESET << latest_day << CYAN << " day(s) journey's progress: \n";

		cout << GREEN "\nYour current rank: ";

		if (total_points >= 5250)
			cout << MAGENTA;
		else if (total_points >= 4500)
		{
			cout << CYAN;
			remain_pts = 5250;
			next_color = MAGENTA;
			next_rank = "🌟 Al-Muhsin";
		}
		else if (total_points >= 3750)
		{
			cout << BLUE;
			remain_pts = 4500;
			next_color = CYAN;
			next_rank = "💎 Al-Muttaqi";			// هنا بنعمل لون الكلام حسب الرانك بتاعه و بنحدد الرانك القادم و اللون القادم و الرانك القادم بيبدأ من كام نقطة عشان نطبعهم تحت
		}
		else if (total_points >= 3000)
		{
			cout << GREEN;
			remain_pts = 3750;
			next_color = BLUE;
			next_rank = "🥇 Al-Mukhlis";
		}
		else if (total_points >= 2250)
		{
			cout << YELLOW;
			remain_pts = 3000;
			next_color = GREEN;
			next_rank = "🥈 Al-Mujtahid";
		}
		else if (total_points >= 1500)
		{
			cout << WHITE;
			remain_pts = 2250;
			next_color = YELLOW;
			next_rank = "🥉 Al-Multazim";
		}
		else if (total_points >= 750)
		{
			cout << GRAY;
			remain_pts = 1500;
			next_color = WHITE;
			next_rank = "🌱 Al-Muwazib";
		}
		else
		{
			cout << RED;
			remain_pts = 750;
			next_color = GRAY;
			next_rank = "⚠️ Al-Muhawil";
		}

		if (total_points < 5250)  // الطباعة لو هو مش أخر رانك
			cout << current_rank << " : ------(" << RESET << total_points << " / " << remain_pts << next_color << ")------ " << next_rank
			<< YELLOW << "  (" GREEN << " Keep Going!" << YELLOW << "😊" << YELLOW << " )";
		else if (total_points >= 5250) // الطباعة لو هو أخر رانك
			cout << current_rank << " : ------(" << RESET << total_points << " / - " << MAGENTA << ")------ "
			<< YELLOW << "  (" GREEN << " Great Job!" << YELLOW << "😊" << YELLOW << " )";

		cout << GREEN << "\nYour current points: " << YELLOW << total_points << GREEN << " !\n"; // بنطبع عدد نقاطه

		cout << GREEN "\nYou have prayed " << YELLOW << total_prayers << GREEN << " prayers out of " << YELLOW << "150" << GREEN
			<< " prayers, You have completed " << YELLOW << (total_prayers / 150.f) * 100 << "%" << GREEN << " of Ramadan's prayers!\n"; // بنطبع عدد صلواته

		cout << GREEN << "\nYou have prayed " << YELLOW << total_bonus_prayers << GREEN << " bonus prayers!" << YELLOW << " [Taraweeh / Tahajud]\n"; //بنطبع عدد صلواته البونص

		cout << GREEN << "\nYou have done tasbeeh " << YELLOW << total_tasbeeh << GREEN << " times, by an average of " // بنطبع عدد تسبيحاته
			<< YELLOW << total_tasbeeh / latest_day << GREEN << " Tasbeeha every day!\n";

		cout << GREEN << "\nYou have achieved you daily goal " << YELLOW << total_goals_achieved << GREEN			// بنطبع كام مرة حقق هدفه اليومي
			<< " times, your success rate is " << YELLOW << (total_goals_achieved / (1.f * latest_day)) * 100 << "% " << GREEN << "!\n";

		cout << RESET << "\nTo " << RED << "RETURN " << RESET << "press " << RED << "Any Key ";		// هنا يرجع للمنيو
		ret = _getch();
		mainmenu();
	}
}

//***********************************************************************************/

void edit_logs() // دالة التعديل
{
	system("cls");
	char e;


	cout << YELLOW << "DO you want to edit your logs?\n\n" << CYAN << "[E] " << RESET << "Edit Logs\n\n" << CYAN << "[Any Key] " << RESET << "Return To Main Menu";
	e = _getch();										// بنسأله لو عايز يعدل أو يرجع للمنيو عشان لو داس بالغلط 
	if (e != 'e' && e != 'E')
	{
		mainmenu();
	}
	else if (e == 'e' || e == 'E')
	{
		system("cls");

		daily_progress edit;
		int l;
		int counter = 0;
		bool check = false;
		bool empty = true;
		int ids[10] = {};
		int used_days[10] = {};
		bool used_day = false;
		for (int i = 0; i < 10; i++)
		{

			if (savedid == logs[i].user_id)	// هنا بنطبع كل السجلات الخاصة بيه
			{
				used_days[counter] = logs[i].ramadan_day; // بنسجل أيام رمضان اللي في السجل بتاعه عشان ميعدلش يوم تاني ليها
				ids[counter] = i; // بنسجل اللوج أيدي بتاعته كلها عشان يختار مابينهم
				counter++; // ده عداد عشان نسجل الحاجة بالترتيب في الأراي من انديكس 0 للأخر
				empty = false; // لو الدالة دخلت هنا يبقى هو عنده سحلات قبل كدة لو مدخلتش يبقى مش عنده و هيفضل ترو
				cout << CYAN << "log id : " << RESET << logs[i].log_id << YELLOW << "\n---------------------------" << GREEN << "\n-" << YELLOW << "Ramadan Day : "
					<< GREEN << logs[i].ramadan_day << "\n-" << YELLOW "Five Prayers : ";
				for (int z = 0; z < 5; z++)
				{
					if (logs[i].Five_prayers[z] == 1)
					{
						cout << GREEN;
					}
					else if (logs[i].Five_prayers[z] == 0)		// هنا بنطبع صلواته في السجل
					{
						cout << RED;
					}
					cout << logs[i].Five_prayers[z] << " ";
				}
				cout << GREEN << "\n-" << YELLOW << "Bonus Prayers : ";
				for (int x = 0; x < 2; x++)
				{
					if (logs[i].Bonus_prayers[x] == 1)
					{
						cout << GREEN;
					}
					else if (logs[i].Bonus_prayers[x] == 0) // هنا بنكبع صلواته البونص في السجل
					{
						cout << RED;
					}
					cout << logs[i].Bonus_prayers[x] << " ";
				}
				cout << GREEN << "\n-" << YELLOW << "Daily Goal : ";
				if (logs[i].daily_goal == 1)
				{
					cout << GREEN << "Achieved";
				}
				else if (logs[i].daily_goal == 0)			// هنا بنطبع نتيجة هدفه اليومي في السجل
				{
					cout << RED << "Not Achieved";
				}
				cout << GREEN << "\n-" << YELLOW << "Current Quran Juz : ";
				if (logs[i].Quran_Juz > 0)
				{
					cout << GREEN;
				}
				else if (logs[i].Quran_Juz == 0)		// هنا بنطبع جزء القرأن في السجل
				{
					cout << RED;
				}
				cout << logs[i].Quran_Juz << " " << YELLOW << "\n---------------------------\n\n";
			}
		}
		if (empty) // لو فضلت ترو يبقى هو معندوش أي سجلات قديمة
		{
			cout << YELLOW << "You don't have any logs yet.";
			cout << RESET << "\n\nTo " << RED << "RETURN " << RESET << "press " << RED << "Any Key ";
			e = _getch();
			mainmenu();
		}
		else
		{
			cout << RESET << "Enter the log id of the log you wish to edit : "; // لو مش ترو يبقى عنده سجلات قديمة اللي عرضناها له و بنخليه يدخل اللوج ايدي اللي عايز يعدل عليه
			l = check_valid_number(0, 9);
		}

		for (int i = 0; i < 10; i++)
		{
			if (ids[i] == l)		// هنا بنشوف لو اللوج أيدي اللي دخله موجود في اللوج ايدي اللي سجلناها فوق
				check = true;
		}
		while (!check)
		{
			cout << RED << "\nLog id doesn't exist." << RESET << "\n\nPlease renter the log id of the log you wish to edit : ";	 // لو مش موجود بنخليه يدخله تاني وهكذا لحد ما يدخل رقم مظبوط
			l = check_valid_number(0, 9);
			for (int i = 0; i < 10; i++)
			{
				if (ids[i] == l)
					check = true;  // لو موجود بنخليها ترو وبندخل اللوب اللي تحت
			}
		}
		if (check)
		{
			system("cls");
			cout << CYAN << "log id : " << RESET << logs[l].log_id << YELLOW << "\n---------------------------" << GREEN << "\n-" << YELLOW << "Ramadan Day"
				<< RESET << "(" << logs[l].ramadan_day << "): "; edit.ramadan_day = check_valid_number(0, logs[l].ramadan_day); // بنطبع له النتيجة القديمة وبنخليه يدخل الجديدة
			for (int i = 0; i < 10; i++)
			{
				if (edit.ramadan_day == used_days[i] && edit.ramadan_day != logs[l].ramadan_day)
				{
					used_day = true;		// هنا بنشوف لو اليوم اللي دخله موجود في السجلات القديمة اللي خزنناها فوق
				}

				if (used_day == true)	// لو موجود في السجلات القديمة بنقول إنه موجود وبنخليه يدخل يوم غيره
				{
					cout << RED << "\nThis day exists in a different log, Please re-enter:" << RESET << "\n\nWhich day of ramadan ?  ";
					edit.ramadan_day = check_valid_number(0, logs[l].ramadan_day);
					i = -1; // بنخلي المتغير ب -1 عشان لما يزيد يبقى صفر ويمشي اللوب كلها مظبوط تاني
					used_day = false; // بنخلي ديه ب فولس عشان يرجع يتشيك عليها فوق لو بقت ترو يدخل هنات اني
				}
			}

		}
		cout << CYAN << "\nEnter one by one:" << GREEN << "\n-" << YELLOW "Five Prayers" << RESET << "( ";
		for (int i = 0; i < 5; i++)
		{
			cout << logs[l].Five_prayers[i] << " ";
		}
		cout << ") ";
		// هنا بنعرض له صلواته القديمة وبنخليه يغيرها واحدة واحدة ورا واحدة
		for (int i = 0; i < 5; i++)
		{
			edit.Five_prayers[i] = check_valid_number(0, 1);
			cout << " ";
		}

		cout << GREEN << "\n-" << YELLOW << "Bonus Prayers : " << RESET << "( ";

		for (int i = 0; i < 2; i++)
		{
			cout << logs[l].Bonus_prayers[i] << " ";
		}
		cout << ") ";
		// هنا بنعرض له الصلوات البونص القديمة وبنخليه يدخلها واحدة ورا واحدة
		for (int i = 0; i < 2; i++)
		{
			edit.Bonus_prayers[i] = check_valid_number(0, 1);
			cout << " ";
		}
		cout << GREEN << "\n-" << YELLOW << "Daily Goal" << RESET << "( " << logs[l].daily_goal << " ) ";		// بنحليه يدخل نتيجة هدفه اليومي
		edit.daily_goal = check_valid_number(0, 1);

		cout << GREEN << "\n-" << YELLOW << "Current Quran Juz" << RESET << "( " << logs[l].Quran_Juz << " ) "; // بنخليه يدخل جزء القرآن
		edit.Quran_Juz = check_valid_number(0, 30);

		upd_reports(logs[l], edit);	//بعتنا السجل القديم و بعد التعديل ل دالة ابديت ريبورتس عشان تحدثه


		cout << YELLOW << "\n\nWould you like edit any other logs?\n\n" << CYAN << "[E] " << RESET << "Edit Logs\n\n" << CYAN << "[Any Key] " << RESET << "Return To Main Menu";
		// هنا بنسأله لو حابب يعدل أي سحل تاني بعد ما حدثنا اللي عمله دلوقتي أو يرجع للمنيو
		e = _getch();
		if (e == 'e' || e == 'E')
		{
			edit_logs();
		}
		else if (e != 'e' && e != 'E')
		{

			mainmenu();
		}


	}
}
//***********************************************************************************/
void reverse_ar(string ar_text) {

	for (int i = ar_text.size() - 1; i >= 0; i -= 2) {
		if (ar_text[i] == ' ') {
			i--;
			cout << " ";
		}

		if (i > 0)
			cout << ar_text[i - 1] << ar_text[i];
	}
}

//*************************************************************************************
void print_ar(string arrabic) {
	vector<string> segments;
	string wait = "";
	int Counter = 0;

	for (int i = 0; i < arrabic.size(); i++) {
		wait += arrabic[i];

		if (arrabic[i] < 0) {
			i++;
			if (i < arrabic.size()) {
				wait += arrabic[i];
			}
		}

		Counter++;

		if (Counter >= 90 && arrabic[i] == ' ') {//بنغير عدد الكلمات من الرقم هنا
			segments.push_back(wait);
			wait = "";
			Counter = 0;
		}
	}

	if (wait != "") {
		segments.push_back(wait);
	}

	for (int i = 0; i < segments.size(); i++) {
		reverse_ar(segments[i]);
		cout << endl;
	}
}
//*******************************************************************************


//****************************************************************************/
void hadith_of_day()
{
	system("cls");
	int ran = rand() % 10;
	cout << zagrapha << endl;
	cout << YELLOW;
	cout << "\n \n \n \n \n";
	print_ar(hadiths[ran]);
	cout << RESET;
	cout << endl;
}


//******************************************************************************************
int check_valid_number(int min_value, int max_value)// هنا بتدخل حدود الحاجه الي انت عاوزه يتشيك
{
	int input_num;

	while (true) {
		cin >> input_num;

		// buffre لو المستخدم دخل حروف هنلغي تاثير الايرور وننضف ال 
		if (cin.fail()) {
			cout << RED << "Invalid! you entered text, Try again with number between  "
				<< min_value << " and " << max_value << RESET;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		/*صلي علنبي
	  الكود ده بيستخدم لو دخل رموز زياده حتى لو مساقه
*/
		cin.ignore(10000, '\n');

		if (cin.gcount() > 1) {
			cout << RED << "Warning: Extra characters detected! Enter strictly one number between : "
				<< min_value << " and " << max_value << RESET;
			continue;
		}

		// ده اظن واضح بيعمل ايه
		if (input_num < min_value || input_num > max_value) {
			cout << RED << "Out of range! Please enter a number between  "
				<< min_value << " and " << max_value << ": " << RESET;
			continue;
		}


		return input_num;
	}
}

//**************************************** */


void search_for_day(int day_Number) {
	ifstream file("calendar.txt");
	string line;
	// day +  بنعمل نفس الصيغه الي هيدور عليها في الملف على شكل رقم
	//to_string بتحول رقم الى string

	string target = "Day " + to_string(day_Number);
	bool found = false;

	if (file.is_open()) {
		while (getline(file, line))// بيفضل يمشي علملف سطر سطر 
		{
			// لو لقينا السطر اللي فيه "Day number"
			if (line == target) {
				found = true;
				cout << RESET << " prayer time for " << line << ":\n";

				int box_width = 28;
				cout << string(box_width, '*') << endl;// بيطبع 30 نجمه

				// بيمشي يطبع توقيتات الصلاوات الخمسه
				for (int i = 0; i < 6; i++) {
					if (getline(file, line)) {
						cout << "* " << CYAN << left << setw(box_width - 4) << line << RESET << " *" << endl;

					}
				}

				if (getline(file, line)) {
				}

				cout << string(box_width, '*') << endl;

				break; //  ai تمت المهمه بنجاح مش عارف ليه بكتب كومينتات اكني 

			}
		}
		if (!found) cout << RED << "Day not found in file\n" << RESET << endl;// لو ملقاش اليوم
		file.close();
	}
	else {
		cout << RED << "Could not open calendar.txt\n" << RESET << endl; // لو ملقاش الملف
	}
}


void add_minute(int& hour, int& minute) {
	minute++;
	if (minute == 60) {
		minute = 0;
		hour++;
	}
}


//******************************************** */

void generate_full_calendar() {
	ofstream calendar_file("calendar.txt");
	prayers month[30];


	month[0].fajr = { 4, 41 };
	month[0].sunrise = { 6, 15 };
	month[0].dhuhr = { 12, 52 };
	month[0].asr = { 4, 30 };
	month[0].maghrib = { 7, 54 };
	month[0].isha = { 8, 54 };

	string period = "AM";

	for (int i = 0; i < 30; i++) {
		calendar_file << "Day " << i + 1 << endl;


		calendar_file << PURPLE << "fajr    : " << setfill('0') << CYAN << setw(2) << month[i].fajr.hour << ":" << setw(2) << month[i].fajr.minutes << PURPLE << " AM " << "  🌄 " << RESET << endl;
		calendar_file << PURPLE << "sunrise : " << setfill('0') << CYAN << setw(2) << month[i].sunrise.hour << ":" << setw(2) << month[i].sunrise.minutes << PURPLE << " AM " << "  🌅 " << RESET << endl;


		int d_h = month[i].dhuhr.hour;
		if (d_h == 13)
			d_h = 1;

		period = (d_h == 12 || d_h == 1) ? "PM " : "AM ";
		calendar_file << PURPLE << "dhuhr   : " << setfill('0') << CYAN << setw(2) << d_h << ":" << setw(2) << month[i].dhuhr.minutes << " " << PURPLE << period << "  ☀️  " << RESET << endl;

		calendar_file << PURPLE << "asr     : " << setfill('0') << CYAN << setw(2) << month[i].asr.hour << ":" << setw(2) << month[i].asr.minutes << PURPLE << " PM " << "  🌤️  " << RESET << endl;
		calendar_file << PURPLE << "maghrib : " << setfill('0') << CYAN << setw(2) << month[i].maghrib.hour << ":" << setw(2) << month[i].maghrib.minutes << PURPLE << " PM " << "  🌇 " << RESET << endl;
		calendar_file << PURPLE << "isha    : " << setfill('0') << CYAN << setw(2) << month[i].isha.hour << ":" << setw(2) << month[i].isha.minutes << PURPLE << " PM " << "  🌌 " << RESET << endl;
		calendar_file << "-------------------" << endl;

		if (i < 29) {
			month[i + 1] = month[i];
			add_minute(month[i + 1].fajr.hour, month[i + 1].fajr.minutes);
			add_minute(month[i + 1].sunrise.hour, month[i + 1].sunrise.minutes);
			add_minute(month[i + 1].dhuhr.hour, month[i + 1].dhuhr.minutes);
			add_minute(month[i + 1].asr.hour, month[i + 1].asr.minutes);
			add_minute(month[i + 1].maghrib.hour, month[i + 1].maghrib.minutes);
			add_minute(month[i + 1].isha.hour, month[i + 1].isha.minutes);
		}
	}
	calendar_file.close();
	cout << "\033[32mSuccess: Calendar regenerated accurately for 30 days!\033[0m\n";
}
//***************************************** */




//هنحط الملف كله في فكتور بعدين نعدل على الفيكتور بعدين نعمل ملف تاني ونحط الفيكتور فيه
// عشان الملف مينفعش تعدل سطر معين بسهوله لازم تقيس البتات وحوار كبير فدي طريقه سهله

void modify_calender(int day, string target_prayer, string new_time) {
	vector<string> fileLines;
	string line;

	ifstream inFile("calendar.txt"); // vector فتحنا الملف عشان نبتدي نخزن السطور في 
	if (!inFile.is_open()) {
		cout << RED << "Error: Cannot open calendar.txt\n" << RESET; // لو مفتحش حذر المستخدم
		return;
	}

	//getline بتاخد سطر سطر لحد ال "/n"
	while (getline(inFile, line)) {
		fileLines.push_back(line);// هنا  بنخزنه
	}
	inFile.close();

	string targetDayMarker = "Day " + to_string(day); // بنحول الرقم لاسترينج عشان نسرع البحث
	//هنحسب مكان السطر ده في الفيكتور بناءا على المعادله الي تحت دي
	int prayer_line = 0;
	if (target_prayer == "fajr") prayer_line = 1;
	else if (target_prayer == "sunrise") prayer_line = 2;
	else if (target_prayer == "dhuhr") prayer_line = 3;
	else if (target_prayer == "asr") prayer_line = 4;
	else if (target_prayer == "maghrib") prayer_line = 5;
	else if (target_prayer == "isha") prayer_line = 6;
	int target_index = ((day - 1) * 8) + prayer_line;
	// بنتشيك ال  bound بتاعت الفيكتور
	if (target_index < fileLines.size() && prayer_line != 0) {
		// بيعدل السطر المطلوب
		fileLines[target_index] = target_prayer + "    : " + new_time;

		//        بيكتبهم كلهم تاني
		ofstream outFile("calendar.txt");
		for (int i = 0; i < fileLines.size(); i++) {
			outFile << fileLines[i] << endl;
		}
		outFile.close();

		cout << GREEN << "Done! Check your folder for modifyed calendar.txt\n" << RESET;
	}
	else {

		cout << RED << "index out of bouns or invalid prayer\n" << RESET;
	}
}


void Special_EVENT(int special_day)
{




	bool found_event = false;  // بيعرفنا لو ملقيناش حدش عشان نطبع تحت خالص
	if (special_day == 1)
	{
		cout << "*********************************************************************************\n";
		cout << "* " << PURPLE << "Welcome Ramadan! Let's start the month with pure hearts and good intentions(:" << RESET << " *\n";
		cout << "*********************************************************************************\n\n";
		found_event = true;
	}


	if (special_day == 15)
	{
		cout << "************************************************************************\n";
		cout << "* " << BLUE << "We are halfway through Ramadan! Keep your energy high and stay active" << RESET << "*\n";
		cout << "************************************************************************\n\n";
		found_event = true;
	}

	if (special_day >= 21 && special_day % 2 != 0)
	{
		cout << "*****************************************************************************************\n";
		cout << "* " << BLUE << "It might be Laylat al-Qadr tonight. Let's pray hard and ask Allah for what we need (:" << RESET << " *\n";
		cout << "*****************************************************************************************\n\n";
		found_event = true;
	}

	if (special_day == 7 || special_day == 14 || special_day == 21 || special_day == 28)
	{
		cout << "********************************************************************\n";
		cout << "* " << BLUE << "Today is Friday! Let's make lots of Dua and read Surah Al-Kahf(: " << RESET << "*\n";
		cout << "********************************************************************\n\n";
		found_event = true;
	}
	if (special_day == 30)
	{
		cout << "***************************************************************************\n";
		cout << "* " << PURPLE << "Ramadan is leaving us... we will miss its light and peace):            " << RESET << " *\n";
		cout << "* " << GREEN << "But we celebrate the gift of Eid! Eid Mubarak to you and your family!(:" << RESET << " *\n";
		cout << "***************************************************************************\n\n";
		found_event = true;
	}

	if (!found_event)
	{
		cout << "\n" << "No special events for today. Keep up your daily prayers!" << "\n\n";
	}


}


void saveAthkarToFile(Athkar library[], int size) {

	ofstream outFile("athkar_data.txt");

	for (int i = 0; i < size; i++) {
		outFile << library[i].thikrID << endl;
		outFile << library[i].category << endl;
		outFile << library[i].content << endl;
		outFile << library[i].targetRepetition << endl;
	}
	outFile.close();
}



void loadAthkarFromFile(Athkar library[], int& size) {
	ifstream inFile("athkar_data.txt");

	//تعديل 
	if (inFile.peek() == EOF) {
		size = 12;
		saveAthkarToFile(library, size);
	}

	else size = 0;


	string tempID, tempCat, tempCont, tempTarget;

	while (getline(inFile, tempID) &&
		getline(inFile, tempCat) &&
		getline(inFile, tempCont) &&
		getline(inFile, tempTarget)) {

		library[size].thikrID = stoi(tempID);
		library[size].category = tempCat;
		library[size].content = tempCont;
		library[size].targetRepetition = stoi(tempTarget);

		size++;
	}
	inFile.close();
}


void adminModuleAthkar(Athkar library[], int& size) {
	while (true) {
		system("cls");
		cout << "===========================================" << endl;
		cout << BLUE;
		cout << "        ATHKAR ADMIN CONTROL PANEL         " << endl;
		cout << RESET;
		cout << "===========================================" << endl;

		for (int i = 0; i < size; i++) {
			if (i % 2 == 0)cout << GREEN;
			else cout << CYAN;
			cout << "ID: " << library[i].thikrID;
			cout << " | Cat: " << library[i].category;
			cout << " | Target: " << library[i].targetRepetition << endl;
			cout << "Content: "; print_ar(library[i].content);
			cout << endl;
			cout << "-------------------------------------------" << endl;
		}

		cout << BLUE << "\n1. Add New Thikr" << endl;
		cout << "2. Remove Thikr (By ID)" << endl;
		cout << "3. Edit Existing Thikr" << endl;
		cout << "4. Return Admin Menu" << endl;
		cout << "Choose option: " << RESET;

		int mainChoice;
		cin >> mainChoice;
		switch (mainChoice) {
		case 1: {
			char addMore = 'k';
			while (addMore == 'k' || addMore == 'K') {
				Athkar newItem;

				newItem.thikrID = library[size - 1].thikrID + 1;

				cout << "\n--- Adding New Thikr (ID: " << newItem.thikrID << ") ---" << endl;
				cout << "Enter Content (Arabic): ";
				cin.ignore();
				getline(cin, newItem.content);
				int catChoice = 0;
				while (catChoice < 1 || catChoice > 4) {
					cout << "Select Category (1.Morning, 2.Evening, 3.After Prayer, 4.Before Sleep): ";
					cin >> catChoice;
					if (catChoice == 1) newItem.category = "Morning";
					else if (catChoice == 2) newItem.category = "Evening";
					else if (catChoice == 3) newItem.category = "After Prayer";
					else if (catChoice == 4) newItem.category = "Before Sleep";
					else cout << "!! Invalid selection. Choose 1-4." << endl;
				}
				cout << "Enter Target Repetition: ";
				cin >> newItem.targetRepetition;
				library[size] = newItem;
				size++;
				saveAthkarToFile(library, size);
				cout << "\nAdded! Press 'k' to add more, or 'b' to return to Admin Menu: ";
				cin >> addMore;
			}
			break;
		}
		case 2: {
			char remMore = 'k';
			while (remMore == 'k' || remMore == 'K') {
				cout << "\nEnter ID to remove: ";
				int targetID, foundIdx = -1;
				cin >> targetID;
				for (int i = 0; i < size; i++) {
					if (library[i].thikrID == targetID) {
						foundIdx = i;
						break;
					}
				}
				if (foundIdx != -1) {
					for (int i = foundIdx; i < size - 1; i++) {
						library[i] = library[i + 1];
					}
					size--;
					saveAthkarToFile(library, size);
					cout << "Thikr " << targetID << " removed." << endl;
				}
				else {
					cout << "Error: ID not found!" << endl;
				}
				cout << "Press 'k' to remove another, or 'b' to return to Admin Menu: ";
				cin >> remMore;
			}
			break;
		}
		case 3: {
			char editMore = 'k';
			while (editMore == 'k' || editMore == 'K') {
				cout << "\nEnter ID to edit: ";
				int targetID, idx = -1;
				cin >> targetID;
				for (int i = 0; i < size; i++) {
					if (library[i].thikrID == targetID) { idx = i; break; }
				}
				if (idx != -1) {
					cout << "\nEditing ID " << targetID << ":" << endl;
					cout << "1. Content\n2. Category\n3. Target\nChoice: ";
					int part; cin >> part;
					if (part == 1) {
						cout << "New Content: "; cin.ignore();
						getline(cin, library[idx].content);
					}
					else if (part == 2) {
						int c = 0;
						while (c < 1 || c > 4) {
							cout << "New Category (1.Morning, 2.Evening, 3.After Prayer, 4.Before Sleep): ";
							cin >> c;
							if (c == 1) library[idx].category = "Morning";
							else if (c == 2) library[idx].category = "Evening";
							else if (c == 3) library[idx].category = "After Prayer";
							else if (c == 4) library[idx].category = "Before Sleep";
						}
					}
					else if (part == 3) {
						cout << "New Target: "; cin >> library[idx].targetRepetition;
					}
					saveAthkarToFile(library, size);
					cout << "Updated Successfully!" << endl;
				}
				else {
					cout << "Error: ID not found!" << endl;
				}
				cout << "Press 'k' to edit another, or 'b' to return to Admin Menu: ";
				cin >> editMore;
			}
			break;
		}
		case 4: {

			adminmenu();


		}
		default:
			cout << RED << "Invalid option!" << endl;
			Sleep(1000);
			break;
		}
	}
}


void runAthkarModule(Athkar library[], int size, string selectedCategory) {
	char input;
	int athkarCount = 0;

	for (int i = 0; i < size; i++)
	{
		if (library[i].category == selectedCategory) {
			athkarCount++;
			int currentCount = 0;
			while (currentCount < library[i].targetRepetition) {
				system("cls");

				cout << YELLOW << "\n--- Thikr " << athkarCount << " From " << selectedCategory << " ---" << RESET << endl;
				cout << "Content: ";
				print_ar(library[i].content);
				cout << "\n--------------------------------------" << endl;
				cout << "Target: " << library[i].targetRepetition << endl;
				cout << "Press 'x' to count (Done: " << currentCount << "): ";

				input = _getch();
				if (input == 'x' || input == 'X') {
					currentCount++;
				}
			}
		}
	}

	system("cls");
	cout << GREEN << "\n** You finished all " << selectedCategory << " athkar! **" << RESET << endl;
	char c = _getch();//عشان نشوف الرساله اللي فوقيها
}





void show_athkar() {
	//خلي بالك ال سي كابيتال
	int Choice;

	while (true) {
		system("cls");
		cout << CYAN "=== Athkar Library Menu ===" << RESET << endl;
		cout << "1. Morning\n2. Evening\n3. After Prayer\n4. Before Sleep \n5. Main Menu " << endl;
		cout << "Choose (1-5): ";

		cin >> Choice;


		if (Choice == 1) runAthkarModule(myLibrary, currentSize, "Morning");
		else if (Choice == 2) runAthkarModule(myLibrary, currentSize, "Evening");
		else if (Choice == 3) runAthkarModule(myLibrary, currentSize, "After Prayer");
		else if (Choice == 4) runAthkarModule(myLibrary, currentSize, "Before Sleep");
		else if (Choice == 5) mainmenu();
		else {
			cout << RED << "\nInvalid Choice! Please enter 1, 2, 3, or 4." << RESET;
			Sleep(3000);
		}
	}
}

void Editing_and_Show_calendar()



{

	ifstream check_file("calendar.txt");
	if (!check_file) {
		generate_full_calendar();
	}
	else {
		check_file.close();
	}

	char keep_running;

	do {
		system("cls");//تعديلي
		int choice;
		int target_day;
		cout << "=========================\n";
		cout << "=Prayer Calendar System =\n";
		cout << "=========================\n\n";
		if (isadmin == 0)
		{
			cout << "1.Search for a Day\n\n";
			cout << "2.View Special Events\n\n";
			cout << "choose an option (1,2)\n\n";
			choice = check_valid_number(1, 2);

		}
		else
		{
			cout << "1.Search for a Day\n\n";
			cout << "2.View Special Events\n\n";
			cout << "3.modify a Prayer Time\n\n";
			cout << "4.Reset ALL calender with acurate time\n\n";
			cout << "Choose an option (1 , 2 , 3 , 4):\n\n";
			choice = check_valid_number(1, 4);
		}


		if (choice == 1)
		{
			cout << "\n enter the day you need to search for, from 1 to 30 ";
			target_day = check_valid_number(1, 30);
			cout << "\n";
			search_for_day(target_day);

		}


		else if (choice == 2)
		{
			cout << "enter the day from 1 to 30: \n";
			int special_day = check_valid_number(1, 30);
			cout << "\n\n";
			Special_EVENT(special_day);

		}



		else if (choice == 3)
		{

			cout << "1.enter The Day You Need To Modify, from 1 to 30 :";
			int modify_day = check_valid_number(1, 30);
			cout << "\n";
			cout << "enter the number of target prayer(from 1 to 6) you need to modify :\n\n";
			cout << "1.Fajr\n";
			cout << "2.Sunrise\n";
			cout << "3.Dhuhr\n";
			cout << "4.Asr\n";
			cout << "5.Maghrib\n";
			cout << "6.ISha\n";
			int day_OF_TARGEtPRAYER = check_valid_number(1, 6);
			string target_prayer;
			switch (day_OF_TARGEtPRAYER)
			{
			case 1:
				target_prayer = "fajr";
				break;

			case 2:
				target_prayer = "sunrise";
				break;

			case 3:
				target_prayer = "dhuhr";
				break;

			case 4:
				target_prayer = "asr";
				break;

			case 5:
				target_prayer = "maghrib";
				break;

			case 6:
				target_prayer = "isha";
				break;
			}

			cout << "enter the new time for:" << target_prayer << "\n";
			cout << "Hours (1-12):\n";
			int new_hour = check_valid_number(1, 12);

			cout << "Minutes (0-59):\n";
			int new_minute = check_valid_number(0, 59);

			cout << "AM or PM ? (Type 1 for AM, 2 for PM):\n";
			int p_choice = check_valid_number(1, 2);
			string period = (p_choice == 1) ? "AM" : "PM";

			// تجميع الوقت في سترينج واحد منسق
			// بنستخدم stringstream عشان نحافظ على شكل الـ 05:05 زي ما عملنا في الـ Calendar
			//string stream بتتحكم في شكل الاستريم بعدين تحوله ل string عادي

			stringstream ss;
			ss << setw(2) << setfill('0') << new_hour << ":"
				<< setw(2) << setfill('0') << new_minute << " " << period;
			string formatted_new_time = ss.str();
			modify_calender(modify_day, target_prayer, formatted_new_time);

		}



		else if (choice == 3)
		{
			generate_full_calendar();

		}
		cout << YELLOW << " Do you want to perform another operation? (y/n):" << RESET;
		cin >> keep_running;
		cin.ignore(10000, '\n'); // yes  عشان لو كتب 
		// ننضف ال buffer



	} while (keep_running == 'y' || keep_running == 'Y');
	cout << BLUE << "thank you for using the calendar system. have a good day (:\n" << RESET;






}




void Show_Calendar() {
	system("cls");
	cout << CYAN "1.To Show Times of Prays \n";
	cout << "2.To Show a Special Event  \n" << RESET;
	char c = _getch();

	if (c == '1') {
		cout << "ENTER THE DAY (1->30) \n";
		int target_day = check_valid_number(1, 30);
		search_for_day(target_day);
		char c = _getch();//عشان نلحق نشوف 
	}
	else if (c == '2') {
		cout << "ENTER THE DAY (1->30) \n";
		int special_day = check_valid_number(1, 30);
		Special_EVENT(special_day);
		char c = _getch();//عشان نلحق نشوف 
	}







}


void Add_new_tasbeeha()
{
	system("cls");
	cout << YELLOW;
	display_for_admin();
	cout << RESET;
	cout << PURPLE << "Enter the string of new tasbeeha \n" << RESET;
	getline(cin, tasabeeh[current_tasbeeha].T);
	tasabeeh[current_tasbeeha].id = current_tasbeeha + 1;
	current_tasbeeha++;
	savetasabeeh(tasabeeh);
	cout << GREEN << "Tasbeeha added successfully!\n" << RESET;
}

void delete_tasbeeha()
{
	system("cls");
	cout << YELLOW;
	display_for_admin();
	cout << RESET;
	cout << PURPLE << "Enter the ID of tasbeeha you want to delete \n" << RESET;
	int id = check_valid_number(1, current_tasbeeha);
	//cin >> id;المتغير اخد القيمه من الداله اللي فوق دي
	for (int i = 0; i < current_tasbeeha; i++)
	{
		if (tasabeeh[i].id == id)
		{
			for (int j = i; j < current_tasbeeha - 1; j++)
			{
				tasabeeh[j] = tasabeeh[j + 1];
				tasabeeh[j].id = j + 1;//تعديل
			}
			current_tasbeeha--;
			savetasabeeh(tasabeeh);
			cout << GREEN << "Tasbeeha deleted successfully!\n" << RESET;
			return;
		}
	}
	cout << RED << "Tasbeeha with ID " << id << " not found.\n" << RESET;
}



void display_for_admin() {
	system("cls");
	for (int i = 0; i < current_tasbeeha; i++)
	{
		cout << "ID" << " " << tasabeeh[i].id << endl;
		cout << "CONTENT " << tasabeeh[i].T << endl;

	}
}

void Editing_tasabeeh()
{
	system("cls");
	cout << CYAN << "1.To Add new tasbeeha \n";
	cout << "2.To delete a tasbeeha \n" << RESET;
	char c = _getch();
	if (c == '1')
	{

		Add_new_tasbeeha();
	}
	else if (c == '2')
	{
		delete_tasbeeha();
	}

	cout << GREEN;//بعد
	display_for_admin();
	char ch = _getch();
	cout << RESET;


}




//******************************** */ ده اكتر كود حديث