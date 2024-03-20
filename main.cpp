//Athour : 7amok4a  by -std=c++17
//Return Dark ^_^ &_&
#include <bits/stdc++.h>
using namespace std;
void Write (vector<string> &db , string &path) {
    auto s = ios::in | ios::out | ios::trunc ;
    fstream fout(path.c_str() , s);
    if (fout.fail()) {
        cout << "Can't open file\n";
        return;
    }
    for (auto &i: db) {
        if (!i.empty()) {
            fout << i << "\n";
        }
    }
    fout.close() ;
}
vector<string> Read (string &path) {
    vector<string> db ;
    ifstream fin ("/home/matter/CLionProjects/Ask Me/Questions.txt") ;
    if (fin.fail()) {
        cout << "Can't open file\n" ;
    }
    string Line ;
    while (getline(fin , Line)) {
        db.push_back(Line) ;
    }
    fin.close() ;
    return db ;
}
void UpdateQuestion (int _id , string &Answer) {
    string path = "/home/matter/CLionProjects/Ask Me/Questions.txt" ;
    vector<string> db = Read(path) ;
    for (auto &i : db) {
        int id , id_p , id_f , id_t ;
        string q , a , Q ;
        char c ;
        istringstream iss (i) ;
        iss >> id >> c >> id_p >> c >> id_f >> c >> id_t >> c ;
        bool flag = 0 ;
        while (getline(iss, Q, ' ')) {
            if (Q == ",")  {
                flag = 1  ;
                continue;
            }
            if (!flag) q += Q, q += " ";
            else a += Q , a += " " ;
        }
        if (_id == id) {
            ostringstream  oss ;
            oss << id << " , " << id_p << " , " << id_f << " , "
                << id_t << " , " << q << " , " << Answer ;
            i = oss.str() ;
            break;
        }
    }
    Write(db , path) ;
}
void DeleteQuestion (int _id) {
    string path = "/home/matter/CLionProjects/Ask Me/Questions.txt" ;
    vector<string> db = Read(path) ;
    for (auto &i : db) {
        int id , id_p , id_f , id_t ;
        string q , a  , Q ;
        char c ;
        istringstream iss (i) ;
        iss >> id >> c >> id_p >> c >> id_f >> c >> id_t >> c ;
        bool flag = 0 ;
        while (getline(iss, Q, ' ')) {
            if (Q == ",")  {
                flag = 1  ;
                continue;
            }
            if (!flag) q += Q, q += " ";
            else a += Q , a += " " ;
        }
        if (_id == id) {
            i = "" ;
        }
    }
    Write(db , path) ;
}
struct User {
    int Id ;
    string Name  , Username , Email , Password ;
    bool Allow_Anonymous  ;
    User() {
        Name = "" , Username = "" , Email = "" , Password = ""  ,
        Allow_Anonymous = true  , Id = -1;
    }
    User (string &username , string &password) {
        Username = username , Password = password ;
    }
    User (string &username , string &name , string &email , string &password , bool allow_Anonymous ) {
        Username = username , Name = name ,
        Email = email , Password = password ,
        Allow_Anonymous = allow_Anonymous ;
    }
    User (int id  , string &username  , string &name , string &email , string &password , bool allow_Anonymous ) {
        Id = id , Username = username ,
        Name = name , Email = email ,
        Password = password  , Allow_Anonymous = allow_Anonymous ;
    }
    User FindUser(string &username , string &password) {
        ifstream  file_handler ("/home/matter/CLionProjects/Ask Me/Users.txt") ;
        if (file_handler.fail()) {
            cout << "Can't open file\n" ;
            return User() ;
        }
        int id ;
        char c ;
        string line , _username , name , email , _password ;
        bool allow_Anonymous ;
        while(getline(file_handler , line)) {
            istringstream iss (line) ;
            iss >> id  >> c >> _username >> c >> name >> c >> email >> c
                >> _password >> c >> allow_Anonymous ;
            if (username == _username and password == _password) {
                return User (id , username , name , email , password , allow_Anonymous);
            }
        }
        file_handler.close() ;
        return User() ;
    }
    User FindUserId (int id) {
        ifstream  file_handler ("/home/matter/CLionProjects/Ask Me/Users.txt") ;
        if (file_handler.fail()) {
            cout << "Can't open file\n" ;
            return User() ;
        }
        int _id ;
        char c ;
        string line , _username , name , email , _password ;
        bool allow_Anonymous ;
        while(getline(file_handler , line)) {
            istringstream iss (line) ;
            iss >> _id  >> c >> _username >> c >> name >> c
                >> email >> c >> _password >> c >> allow_Anonymous ;
            if (id == _id) {
                return User (id , _username , name , email , _password , allow_Anonymous);
            }
        }
        file_handler.close() ;
        return User() ;
    }
    void AddUser() {
        auto state = ios::in | ios::out | ios::app ;
        fstream  file_handler ("/home/matter/CLionProjects/Ask Me/Users.txt"  ,state ) ;
        ifstream fin ("/home/matter/CLionProjects/Ask Me/Users.txt") ;
        if (file_handler.fail() or fin.fail()) {
            cout << "Can't open file\n" ;
            return ;
        }
        string Line ;
        int _id = 0 ;
        char c ;
        string _username , _name , _email , _password ;
        bool _allow;
        while (getline(fin , Line)) {
            istringstream iss(Line) ;
            iss >> _id >> c >> _username >> c >>_name >> c
                >>_email >> c >> _password >> c >> _allow ;
        }
        Id = ++_id ;
        file_handler << Id  << " , " << Username << " , "
                     << Name << " , " << Email << " , "
                     << Password << " , " << Allow_Anonymous << "\n" ;
        fin.close() ;
        file_handler.close() ;
    }
};
struct Question {
    int Id ;
    int Id_Parent  , Id_fromuser  , Id_touser;
    string Question_text , Answer_text ;
    Question() {
        Id_Parent = -1 , Id_fromuser = 0
                , Id_touser = 0 , Question_text = "" , Answer_text = "" ;
    }
    Question(int id_p , int id_f , int id_t , string &NewQuestion ) {
        Id_Parent = id_p , Id_fromuser = id_f , Id_touser = id_t ;
        Question_text = NewQuestion  , Answer_text = "" ;
    }
    Question(int id , int id_p , int id_f , int id_t , string &NewQuestion , string &a) {
        Id = id , Id_Parent = id_p , Id_fromuser = id_f , Id_touser = id_t ;
        Question_text = NewQuestion  , Answer_text = a ;
    }
    void Add_question() {
        auto state = ios::in | ios::out | ios::app ;
        fstream  file_handler ("/home/matter/CLionProjects/Ask Me/Questions.txt" , state) ;
        ifstream  fin ("/home/matter/CLionProjects/Ask Me/Questions.txt" ) ;
        if (file_handler.fail() or fin.fail()) {
            cout << "Can't Open file\n" ;
            return;
        }
        string line ;
        int _id  = 0 , id_p , id_f , id_t  ;
        while (getline(fin, line)) {
            char c ;
            string q , a , Q , A ;
            istringstream iss(line);
            iss >> _id >> c >> id_p >> c >> id_f >> c >> id_t >> c ;
            bool flag = 0 ;
            while (getline(iss, Q, ' ')) {
                if (Q == ",")  {
                    flag = 1  ;
                    continue;
                }
                if (!flag) q += Q, q += " ";
                else a += Q , a += " " ;

            }
        }
        Id = ++ _id ;
        file_handler << Id << " , " << Id_Parent << " , "
                     << Id_fromuser << " , " << Id_touser << " , "
                     << Question_text << " , " << Answer_text  << "\n" ;
        file_handler.close() ;
        fin.close() ;
    }
    Question FindQuestionId (int id) {
        ifstream  fin ("/home/matter/CLionProjects/Ask Me/Questions.txt") ;
        if (fin.fail()) {
            cout << "Can't open file\n" ;
        }
        string line ;
        while (getline(fin, line)) {
            char c ;
            int _id , id_p , id_f , id_t  ;
            string q , a , Q , A ;
            istringstream iss(line);
            iss >> _id >> c >> id_p >> c >> id_f >> c >> id_t >> c ;
            bool flag = 0 ;
            while (getline(iss, Q, ' ')) {
                if (Q == ",")  {
                    flag = 1  ;
                    continue;
                }
                if (!flag) q += Q, q += " ";
                else a += Q , a += " " ;
            }
            if (_id == id) {
                return Question(_id , id_p , id_f , id_t , q , a) ;
            }
        }
        return Question() ;
    }
    string Tostring () {
        ostringstream oss;
        oss << Id << " , " << Id_Parent << " , "
            << Id_fromuser << " , " << Id_touser << " , "
            << Question_text << " , " << Answer_text ;
        return oss.str() ;
    }
};
map<int,vector<Question>> PrintToMe (int _id) {
    map<int,vector<Question>> qestion_to_me ;
    ifstream  fin ("/home/matter/CLionProjects/Ask Me/Questions.txt") ;
    if (fin.fail()) {
        cout << "Can't open file \n" ;
    }
    string line ;

    while (getline(fin, line)) {
        char c ;
        int id , id_p , id_f , id_t  ;
        string q , a , Q ;
        istringstream iss(line);
        iss >> id >> c >> id_p >> c >> id_f >> c >> id_t >> c ;
        bool flag = 0 ;
        while (getline(iss, Q, ' ')) {
            if (Q == ",")  {
                flag = 1  ;
                continue;
            }
            if (!flag) q += Q, q += " ";
            else a += Q , a += " " ;

        }
        if (_id == id_t and id_p == -1) {
            qestion_to_me[id].emplace_back(Question(id ,id_p ,id_f ,id_t , q , a)) ;
        }
        else if (_id == id_t and id_p != -1) {
            qestion_to_me[id_p].emplace_back(Question(id ,id_p ,id_f ,id_t , q , a)) ;
        }
        else {
            continue;
        }
    }
    fin.close() ;
    return qestion_to_me ;
}
void PrintQuestion (int _id) {
    ifstream  fin ("/home/matter/CLionProjects/Ask Me/Questions.txt") ;
    if (fin.fail()) {
        cout << "Can't open file\n" ;
        return;
    }
    string line ;
    while(getline(fin ,line)) {
        char c ;
        int id , id_p , id_f , id_t ;
        string q , Q , a , A ;
        istringstream iss(line);
        iss >> id >> c >> id_p >> c >> id_f >> c >> id_t >> c ;
        bool flag = 0 ;
        while (getline(iss, Q, ' ')) {
            if (Q == ",")  {
                flag = 1  ;
                continue;
            }
            if (!flag) q += Q, q += " ";
            else a += Q , a += " " ;

        }
        if (_id == id_f) {
            cout << "Question Id (" << id << ") to user id(" << id_t << ")\n" ;
            cout << "Question_Text : " << q ;
            if(!a.empty())
                cout << "Answer : " << a << "\n" ;
        }
    }
    fin.close() ;
}
void  PrintAllQuestionsAnswered() {
    string path = "/home/matter/CLionProjects/Ask Me/Questions.txt" ;
    ifstream fin (path.c_str()) ;
    string line ;
    while (getline(fin , line)) {
        char c ;
        int id , id_p , id_f , id_t ;
        string q , Q , a , A ;
        istringstream iss(line);
        iss >> id >> c >> id_p >> c >> id_f >> c >> id_t >> c ;
        bool flag = 0 ;
        while (getline(iss, Q, ' ')) {
            if (Q == ",")  {
                flag = 1  ;
                continue;
            }
            if (!flag) q += Q, q += " ";
            else a += Q , a += " " ;

        }
        if (!a.empty()) {
            cout << "Question Id (" << id << ") from user id (" << id_f
                 << ") to user id (" << id_t << ")\n" ;
            cout << "Text : " << q << "\n"
                 << "Answer : " << a << "\n" ;
        }
    }
}
User Small_choice() {
    while (true) {
        cout << "Menu :\n"
             << "      1 : Login \n"
             << "      2 : Sign Up\n" ;
        int n ; cin >> n ;
        if (n == 1) {
            cout << "Enter Username and Password\n" ;
            string username , password ;
            cin >> username >> password ;
            User u ;
            User flag = u.FindUser(username , password) ;
            if (flag.Id != -1) {
                cout << "Successful Registration , Hallo ^_^ &_&\n" ;
                return flag;
            }
            else {
                cout << "Your Username or Password not correct ^_^ &_&\n" ;
            }
        }
        else if (n == 2) {
            cout << "Hallo ^_^ &_& , Please Enter Data Without Spaces\n" ;
            cout << "-----------------------------------------------------------\n" ;
            cout << "Enter Your Username : " ;
            string username ; cin >> username ;
            cout << "Enter Your Name : " ;
            string name ;   cin >> name ;
            cout << "Enter Your Email : " ;
            string email ;  cin >> email ;
            cout << "Enter Your Password : " ;
            string password ; cin >> password ;
            cout << "Do you need Allow_Anonymous or not , Enter (0 : no , 1 : yes) : " ;
            bool allow_Anonymous ;  cin >> allow_Anonymous ;
            User u (username , name , email , password , allow_Anonymous) ;

            u.AddUser() ;
            cout << "Successful Registration , Hallo ^_^ &_&\n" ;
            return u ;
        }
        else {
            cout << "Invalied Input ^_^ &_&\n" ;
        }
    }
}
void Core() {
    User u = Small_choice();
    while (true) {
        cout << "Menu :\n"
             << "   1 : Print Questions To Me\n"
             << "   2 : Print Questions From Me\n"
             << "   3 : Answer Question\n"
             << "   4 : Delete Question\n"
             << "   5 : Ask Question\n"
             << "   6 : List System Users\n"
             << "   7 : Feed\n"
             << "   8 : Log out\n"
             << "Enter Number in range 1 - 8 : ";
        int n;
        cin >> n;
        if (n == 1) {
            // print question id , qustion to me  , answer if found
            map<int,vector<Question>> qestion_to_me = PrintToMe(u.Id) ;
            for (auto &[l ,r] : qestion_to_me) {
                for (int i = 0 ; i < (int)r.size() ; ++i) {
                    int id , id_p , id_f , id_t  ;
                    string q , a , Q ;
                    char c ;
                    if ( i > 0) {
                        cout << "Thread >> \n" ;
                    }
                    istringstream iss(r[i].Tostring()) ;
                    iss >> id >> c >> id_p >> c
                        >> id_f >> c >> id_t >> c ;
                    bool flag = 0 ;
                    while (getline(iss, Q, ' ')) {
                        if (Q == ",")  {
                            flag = 1  ;
                            continue;
                        }
                        if (!flag) q += Q, q += " ";
                        else a += Q , a += " " ;

                    }
                    cout << "Question id(" << id << ") from User Id (" << id_f << ")\n"
                         << "Text : " << q  ;
                    if (!a.empty())
                        cout << "   Answer : " << a  ;
                    cout << "\n" ;

                }
            }
            cout << "\n" ;
        }
        else if (n == 2) {
                // print Question id , questions form me  , answer is founded
                PrintQuestion(u.Id) ;
                cout << "\n" ;
        }
        else if (n == 3) {
            cout << "Enter Question id or -1 to cancel : ";
            int id;
            cin >> id;
            Question q = q.FindQuestionId(id);
            cout << "Question Id (" << id << ") From User Id (" << q.Id_fromuser << ") \n"
                 << "Question : " << q.Question_text << "\n" << q.Answer_text << "\n";
            if (!q.Answer_text.empty()) {
                cout << "Warining : Already answered . Answer will be updated\n" ;
            }
            cout << "Enter Your Answer : " ;
            string a  , line ;  cin >> a ;
            getline(cin , line) ;
            a += line ;
            UpdateQuestion(id , a) ;
            cout << "\n" ;
        }
        else if (n == 4) {
            cout << "Enter Question id or -1 to cancel : ";
            int id ; cin >> id ;
            DeleteQuestion(id) ;
            cout << "\n" ;
        }
        else if (n == 5) {
            cout << "Enter User id or -1 to cancel : ";
            int id;
            cin >> id;
            User U = U.FindUserId(id);
            if (U.Allow_Anonymous == 0) {
                cout << "Note : Anonymous Questions are not allowed for this User\n";
            }
            cout << "For Thread Question : Enter Question id or -1 for new Question : ";
            int id_Question;
            string _Question  , line;
            cin >> id_Question;
            cout << "Enter Question Text : ";
            cin >> _Question ;
            getline(cin, line) ;
            _Question += line ;
            Question Q(id_Question, u.Id, id, _Question);
            Q.Add_question();
            cout << "\n" ;
        }
        else if (n == 6) {
            ifstream fin ("/home/matter/CLionProjects/Ask Me/Users.txt") ;
            if (fin.fail()) {
                cout << "Can't open file\n" ;
                return;
            }
            string Line ;
            int id  ;
            char c ;
            string username , name , email , password ;
            bool allow ;
            while (getline(fin , Line)) {
                istringstream iss(Line) ;
                iss >> id >> c
                    >> username >> c
                    >> name >> c
                    >> email >> c
                    >> password >> c
                    >> allow ;
                cout << "Id : " << id << "      " << "Name : " << name << "\n" ;
            }
            fin.close() ;
            cout << "\n" ;
        }
        else if (n == 7) {
            PrintAllQuestionsAnswered() ;
            cout << "\n" ;
        }
        else if (n == 8) {
            u = Small_choice() ; 
        }
        else {
            cout << "Invalied Number ^_^ &_&\n";
        }
    }
}
int main() {
    Core() ;
    return 0;
}