#include <bits/stdc++.h>
using namespace std ;

class book ;
class user ;
class session ;
map<pair<string,string>,int> data_base ; // Take user name and password then pop the user id.
vector<string> categories ;
map<string,int> cat_num ;
map<string,bool> USER ;
vector<vector<book>> books ;
class book
{
      private:
            string name ;
            string author ;
            string category ;
            int number_of_pages ;
            vector<string> pages ;
            vector<user> readers ;
      public:
            book()
            {

            }
            book ( string name, string author, string category, int num, vector<string>pages )
            {
                  this->name = name ;
                  this->author = author ;
                  this->category = category ;
                  number_of_pages = num ;
                  this->pages = pages ;
            }
            int get_num_of_pages()
            {
                  return number_of_pages ;
            }
            string get_name()
            {
                  return name ;
            }
            void Details()
            {
                  cout << '\n' ;
                  cout << "| Name: " << name << '\n' ;
                  cout << "| Author: " << author << '\n' ;
                  cout << "| Category: " << category << '\n' ;
                  cout << "| Number of pages: " << number_of_pages << '\n' ;
            }
            string view_page( int i )
            {
                  return pages[i-1] ;
            }
            int get_category ()
            {
                  return cat_num[category] ;
            }
            vector<user> &get_readers()
            {
                  return readers ;
            }
            friend istream &operator >> ( istream &in, book &New ) ;
} ;
istream &operator >> ( istream &in, book &New )
{
      cout << "| Enter book name: ", in >> New.name ;
      cout << "| Enter book category: ", in >> New.category ;
      if ( cat_num.find(New.category) == cat_num.end() )
      {
            cat_num[New.category] = categories.size() ;
            categories.push_back(New.category) ;
            books.push_back({}) ;
      }
      cout << "| Enter book author: ", in >> New.author ;
      cout << "| Enter How many pages: ", in >> New.number_of_pages ;
      cout << '\n' ;
      string page ;
      for ( int i = 0 ; i < New.number_of_pages ; i++ )
      {
            cout << "-- Page #" << i+1 << ": " ;
            in >> page ;
            New.pages.push_back( page ) ;
      }
      return in ;
}
class session
{
      private:
            string category ;
            book Book ;
            int last_page ;
      public:
            session()
            {

            }
            session ( string catogory, book Book, int last_page )
            {
                  this->category = category ;
                  this->Book = Book ;
                  this->last_page = last_page ;
            }
            void next_page()
            {
                  last_page++ ;
            }
            void pervious_page()
            {
                  last_page-- ;
            }
            int get_last_page()
            {
                  return last_page ;
            }
            book get_book ()
            {
                  return Book ;
            }
            string get_category()
            {
                  return category ;
            }
            friend ostream &operator <<( ostream &out, session S ) ;
} ;
ostream &operator <<( ostream &out, session S )
{
      out << S.category << " | " << S.Book.get_name() << " | " <<  "Stopped at page #" << S.last_page ;
      return out ;
}
class user
{
      private:
            string name ;
            string email ;
            string username ;
            bool role ; //admin --> ( 1 ) or reader --> ( 0 ).
            vector<session> my_sessions ;
      public:
            user()
            {

            }
            user ( string name, bool role, string email, string username )
            {
                  this->name = name ;
                  this->role = role ;
                  this->email = email ;
                  this->username = username ;
            }
            void add_book ( )
            {
                  book New ;
                  cin >> New ;
            }
            string get_name ()
            {
                  return name ;
            }
            string get_username()
            {
                  return username ;
            }
            string get_email()
            {
                  return email ;
            }
            string get_role()
            {
                  return ( role ? "Admin" : "Reader" ) ;
            }
            void add_session ( session New )
            {
                  my_sessions.push_back( New ) ;
            }
            vector<session> &get_my_sessions ()
            {
                  return my_sessions ;
            }
            friend ostream &operator <<( ostream &out, user P ) ;
} ;
ostream &operator <<( ostream &out, user P )
{
      out << P.username << " | " << P.name << " | " << P.email << " | " << P.get_role() ;
      if ( P.role == 0 )
      {
            if ( P.get_my_sessions().size() == 0 )
                  out << " ( This user has no sessions ). " ;
            else if ( P.get_my_sessions().size() == 1 )
                  out << " ( This user has 1 session ). " ;
            else
                  out << " ( This user has " << P.get_my_sessions().size() << " sessions )." ;
      }
      return out ;
}
vector<user> users ;
int login ()
{
      string username, password ;
      cout << "| Enter user name: ", cin >> username ;
      cout << "| Enter password: ", cin >> password ;
      if ( cin.fail() || data_base.find({username, password}) == data_base.end() )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n-------------------------------\n" ;
            cout << "| Wrong username or password! |\n" ;
            cout << "-------------------------------\n\n" ;
            return -1 ;
      }
      return data_base[{username, password}] ;
}
user &start() ;
user &signup ()
{
      string username, password, name, email ;
      cout << "| Enter user name: ", cin >> username ;
      cout << "| Enter password: ", cin >> password ;
      cout << "| Enter name: ", cin >> name ;
      cout << "| Enter email: ", cin >> email ;
      cout << '\n' ;
      if ( cin.fail() )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n-----------------------------\n" ;
            cout << "| Please insert valid data! |\n" ;
            cout << "-----------------------------\n\n" ;
            return signup() ;
      }
      if ( USER[username] )
      {
            cout << "\n-----------------------------------\n" ;
            cout << "| This username is already in use |\n" ;
            cout << "-----------------------------------\n\n" ;
            start() ;
      }
      USER[username] = 1 ;
      users.push_back( {name, 0, email, username} ) ;
      user &New = users[users.size() - 1] ;
      data_base[{username, password}] = users.size() - 1 ;
      return New ;
}
user &start()
{
      while ( true )
      {
            cout << "\n----------------------------------------\n" ;
            cout << "| Welcome to SANAD online book reader! |\n" ;
            cout << "----------------------------------------\n" ;
            cout << "[1] login\n[2] sign up\n[3] exit\n" ;
            cout << "| Enter your choice: " ;
            int choice ;
            cin >> choice ;
            cout << '\n' ;
            user *person ;
            if ( cin.fail() || !( choice >= 1 && choice <= 3 ) )
            {
                  cin.clear() ;
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "\n------------------------------------------\n" ;
                  cout << "| Please enter a number in range ( 1 - 2 )! |\n" ;
                  cout << "------------------------------------------\n\n" ;
                  continue ;
            }
            if ( choice == 1 )
            {
                  int num = login() ;
                  if ( num == -1 )
                        continue ;
                  person = &users[num] ;
            }
            else if ( choice == 2 )
                  person = &signup() ;
            else
                  exit(0) ;

            return *person ;
      }
}
void add_admins()
{
      string username, password ;
      user admin1( "Sanad", 1, "Sanad@gmail.com", "Sanad_jr"), admin2( "Sanad2", 1, "Sanad@gmail.com", "Sanad_jr2"), admin3( "Sanad3", 1, "Sanad@gmail.com", "Sanad_jr3") ;
      username = "Sanad_jr", password = "*" ;
      data_base[{username, password}] = users.size() ;
      users.push_back(admin1) ;

      username = "Sanad_jr2", password = "**" ;
      data_base[{username, password}] = users.size() ;
      users.push_back(admin2) ;

      username = "Sanad_jr3", password = "***" ;
      data_base[{username, password}] = users.size() ;
      users.push_back(admin3) ;
}
void add_books_Cat()
{
      categories.push_back( "Programming" ) ;
      categories.push_back( "Marketing" ) ;
      books.push_back({}) ;
      books.push_back({}) ;
      cat_num["Programming"] = 0 ;
      cat_num["Marketing"] = 1 ;
      vector<int> readers ;
      book cpp( "cpp", "Sanad", "Programming", 4, { "Start", "variables", "loops", "arrays"}) ;
      books[0].push_back(cpp) ;
      book java( "java", "Sanad", "Programming", 4, { "Start", "variables", "loops", "arrays"}) ;
      books[0].push_back(java) ;
      book Digital( "Digital_Marketing", "Ahmed", "Marketing", 3, { "Start", "About", "Why_Marketing"}) ;
      books[1].push_back(Digital) ;
}
void start_session( user &person, int num )
{
      session &s = person.get_my_sessions()[num] ;
      while ( true )
      {
            int curr = s.get_last_page() ;
            cout << "{ Page #" << curr << " | " << s.get_book().view_page( curr ) << " }\n" ;
            cout << "-------------\n" ;
            int CH = 1 ;
            if ( curr < s.get_book().get_num_of_pages() )
                  cout << "[" << CH << "] - Next page\n", CH++ ;
            if ( curr > 1 )
                  cout << "[" << CH << "] - Previous page\n", CH++ ;
            cout << "[" << CH << "] - End session\n" ;

            cout << "| Enter your choice: " ;
            int choice ;
            cin >> choice ;
            cout << '\n' ;
            if ( cin.fail() || ! ( choice >= 1 && choice <= CH ) )
            {
                  cin.clear() ;
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "\n----------------------------------------------\n" ;
                  cout << "| Please enter a number in range ( 1 - " << CH << " )! |\n" ;
                  cout << "----------------------------------------------\n\n" ;
                  continue;
            }
            if ( choice == 1 && curr < s.get_book().get_num_of_pages() )
                  s.next_page() ;
            else if ( choice == 1 )
                  s.pervious_page() ;
            else if ( choice == 2 && CH == 3 )
                  s.pervious_page() ;
            else
            {
                  return ;
            }
      }      

}
void select_book ( user &person, book &Book, int category )
{
      cout << "[ Book details: ]\n" ;
      Book.Details() ;
      cout << '\n' ;
      cout << "[1] - Start session\n[2] - Previous page\n" ;
      cout << "| Enter your choice: " ;
      int choice ;
      cin >> choice ;
      cout << '\n' ;
      if ( cin.fail() || !( choice == 1 || choice == 2 ) )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n------------------------------------------\n" ;
            cout << "| Please enter a number in range ( 1 - 2 )! |\n" ;
            cout << "------------------------------------------\n\n" ;
            select_book( person, Book, category ) ;
      }
      if ( choice == 2 )
            return ;
      else
      {
            person.add_session( session(categories[category], Book, 1) ) ; 
            Book.get_readers().push_back( person ) ;
            start_session( person, person.get_my_sessions().size()-1 ) ;
      }
}
void list_books( user &person, int category )
{
      int number = books[category].size() ;
      cout << "| There are found " << number << ( number > 1 ? " books " : " book " ) << "in " << categories[category] << " category\n" ;
      cout << "--------------------------\n" ;
      for ( int i = 0 ; i < number ; i++ )
      {
            cout << "[" << i+1 << "] - " << books[category][i].get_name() << '\n' ;
      }
      cout << "[" << number+1 << "] - Previous page\n\n" ;
      cout << "| Enter your choice: " ;
      int choice ;
      cin >> choice ;
      cout << '\n' ;
      if ( cin.fail() || !( choice >= 1 && choice <= number + 1 ) )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n------------------------------------------\n" ;
            cout << "| Please enter a number in range ( 1 - " << number+1 << " )! |\n" ;
            cout << "------------------------------------------\n\n" ;
            list_books( person, category ) ;
      }
      if ( choice == number + 1 )
            return ;
      else
      {
            select_book( person, books[category][choice-1], category ) ;   
            list_books( person, category ) ;
      }   
}
void View_categories( user &person )
{
      int number = categories.size() ;
      cout << "| There are found " << number << " categories\n" ;
      cout << "------------------\n" ;
      for ( int i = 0 ; i < number ; i++ )
      {
            cout << "[" << i+1 << "] - " << categories[i] << '\n' ;
      }
      cout << "[" << number+1 << "] - Previous page\n\n" ;
      cout << "| Enter your choice: " ;
      int choice ;
      cin >> choice ;
      cout << '\n' ;
      if ( cin.fail() || !( choice >= 1 && choice <= number + 1 ) )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n------------------------------------------\n" ;
            cout << "| Please enter a number in range ( 1 - " << number+1 << " )! |\n" ;
            cout << "------------------------------------------\n\n" ;
            View_categories( person ) ;
      }
      if ( choice == number + 1 )
            return ;
      else
      {
            list_books( person, choice - 1 ) ;
            View_categories( person ) ;
      }
}
void Reading_history ( user &person )
{
      while ( person.get_my_sessions().empty() )
      {
            cout << "\n----------------------------------------\n" ;
            cout << "| You do not have any reading history! |\n" ;
            cout << "----------------------------------------\n\n" ;
            cout << "[1] - List available book categories\n[2] - Previous page\n" ;
            cout << "| Enter your choice: " ;
            int choice ;
            cin >> choice ;
            cout << '\n' ;
            if ( cin.fail() || !( choice == 1 || choice == 2 ) )
            {
                  cin.clear() ;
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "\n------------------------------------------\n" ;
                  cout << "| Please enter a number in range ( 1 - 2 )! |\n" ;
                  cout << "------------------------------------------\n\n" ;
                  continue;
            }
            if ( choice == 1 )
            {
                  View_categories( person ) ;
                  return ;
            }
            else
            {
                  return ;
            }
      }
      vector<session> Sessions = person.get_my_sessions() ;
      int number = Sessions.size() ;
      cout << "| You have " << number << " sessions\n" ;
      cout << "----------------\n" ;
      for ( int i = 0 ; i < number ; i++ )
      {
            cout << "[" << i+1 << "] - " << Sessions[i] << '\n' ;
      }
      cout << "[" << number+1 << "] - Previous page\n" ;
      cout << "| Enter your choice : " ;
      int choice ;
      cin >> choice ;
      cout << '\n' ;
      if ( cin.fail() || !( choice >= 1 || choice <= number + 1 ) )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n------------------------------------------\n" ;
            cout << "| Please enter a number in range ( 1 - " << number+1 << " )! |\n" ;
            cout << "------------------------------------------\n\n" ;
      }
      if ( choice == number + 1 )
            return ;
      else
      {
            start_session( person, choice - 1 ) ;
      }
      

}
void Reader_view( user &person )
{
      cout << '\n' ;
      cout << "| Hello " << person.get_name() << " | " << person.get_role() << " view\n" ;
      cout << "--------------------\n" ;
      cout << "[1] - View profile\n[2] - List & Select from my reading history\n[3] - List available book categories\n[4] - logout\n" ;
      cout << "| Enter your choice: " ;
      int choice ;
      cin >> choice ;
      cout << '\n' ;
      if ( cin.fail() || !( choice >= 1 && choice <= 4 ) )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n------------------------------------------\n" ;
            cout << "| Please enter a number in range ( 1 - 4 )! |\n" ;
            cout << "------------------------------------------\n\n" ;
            Reader_view( person ) ;
      }
      
      if ( choice == 1 )
      {
            cout << "---------------\n" ;
            cout << "Name: " << person.get_name() << "\n" << "Email: " << person.get_email() << "\n" << "Username: " << person.get_username() << "\n" << "Role: " << person.get_role() << '\n' ;
            cout << "---------------\n\n" ;
            Reader_view( person ) ;
      }
      else if ( choice == 2 )
      {
            Reading_history( person ) ;
            Reader_view( person ) ;
      }
      else if ( choice == 3 )
      {
            View_categories( person ) ;
            Reader_view( person ) ;
      }
      else  
            return ;
}
void Add_book()
{
      cout << "| Please enter book Details\n" ;
      cout << "------------------" ;
      book Book ;
      cin >> Book ;
      books[Book.get_category()].push_back( Book ) ;
      return ;
}
void show_sessions( user &person )
{
      int number = person.get_my_sessions().size() ;
      if ( number == 0 )
      {
            cout << "\n------------------------------\n" ;
            cout << "| This user has no sessions! |\n" ;
            cout << "------------------------------\n\n" ;
            return ;
      }
      cout << "| There are found " << number << " " << ( number == 1 ? "session\n" : "sessions\n" ) ;
      cout << "----------------------------\n" ;
      for ( int i = 0 ; i < number ; i++ )
      {
            cout << "[" << i+1 << "] - " << person.get_my_sessions()[i] << '\n' ;
      }
      cout << "\n| Enter 0 for the previous page : " ;
      int choice ;
      cin >> choice ;
      cout << '\n' ;
      if ( cin.fail() || choice != 0 )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n---------------------\n" ;
            cout << "| Not valid choice! |\n" ;
            cout << "---------------------\n\n" ;
            show_sessions( person ) ;
      }
      return ;
}
void list_users()
{
      while ( true )
      {
            int number = users.size() ;
            cout << "| There are found " << number << " " << ( number == 1 ? "user\n" : "users\n" ) ;
            cout << "----------------------------\n" ;
            for ( int i = 0 ; i < number ; i++ )
            {
                  cout << "[" << i+1 << "] - " << users[i] << '\n' ;
            }
            if ( users[number-1].get_role() == "Admin" )
            {
                  cout << "| Enter 0 for the previous page: " ;
                  int choice ;
                  cin >> choice ;
                  cout << '\n' ;
                  if ( cin.fail() || choice != 0 )
                  {
                        cin.clear() ;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\n---------------------\n" ;
                        cout << "| Not valid choice! |\n" ;
                        cout << "---------------------\n\n" ;
                        list_users() ;
                  }
                  return ;
            }
            cout << "[ Enter your choice with the reader's number to show their current sessions, or 0 for the previous page ]\n" ;
            cout << "| Enter your choice: " ;
            int choice ;
            cin >> choice ;
            cout << '\n' ;
            if ( cin.fail() || !( choice >= 0 && choice <= number ) )
            {
                  cin.clear() ;
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "\n------------------------------------------\n" ;
                  cout << "| Please enter a number in range ( 0 - " << number << " )! |\n" ;
                  cout << "------------------------------------------\n\n" ;
                  continue;
            }
            else if ( choice == 0 )
                  return ;
            else if ( users[choice-1].get_role() == "Admin" )
            {
                  cout << "\n--------------------------------\n" ;
                  cout << "| You can't choose from admins! |\n" ;
                  cout << "--------------------------------\n\n" ;
                  continue;
            }
            show_sessions( users[choice-1] ) ;
            list_users() ;
      }
}
void category_datails( int num )
{
      int number = books[num].size() ;
      cout << "| There are found " << number << " " << ( number == 1 ? "book\n" : "books\n" ) ;
      cout << "---------------------\n" ;
      for ( int i = 0 ; i < number ; i++ )
      {
            cout << "[" << i+1 << "] - " << books[num][i].get_name() << " " ;
            if ( !books[num][i].get_readers().empty() )
            {
                  if ( books[num][i].get_readers().size() == 1 )
                        cout << " ( 1 user has sessions with this book ) " ;
                  else
                        cout << " ( " << books[num][i].get_readers().size() << " users have sessions with this book )" ;
            }
            cout << '\n' ;
      }
      cout << "\n| Enter 0 for the previous page : " ;
      int choice ;
      cin >> choice ;
      cout << '\n' ;
      if ( cin.fail() || choice != 0 )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n---------------------\n" ;
            cout << "| Not valid choice! |\n" ;
            cout << "---------------------\n\n" ;
            category_datails( num ) ;
      }
      return ;
}
void list_categories()
{
      int number = categories.size() ;
      cout << "| There are found " << number << " " << ( number == 1 ? "category\n" : "categories\n" ) ;
      cout << "-------------------------\n" ;
      for ( int i = 0 ; i < number ; i++ )
      {
            cout << "[" << i+1 << "] - " << categories[i] << '\n' ;
      }
      cout << "[ Enter the category number to view its details, or 0 for the previous page.] \n" ;
      cout << "| Enter your choice " ;
      int choice ;
      cin >> choice ;
      cout << '\n' ;
      if ( cin.fail() || !( choice >= 0 && choice <= number ) )
      {
            cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n------------------------------------------\n" ;
            cout << "| Please enter a number in range ( 0 - " << number << " )! |\n" ;
            cout << "------------------------------------------\n\n" ;
            list_categories() ;
      }
      else if ( choice == 0 )
            return ;
      category_datails( cat_num[categories[choice-1]] ) ;
      list_categories() ;
}
void Admin_view( user &person )
{
      while ( true )
      {
            cout << '\n' ;
            cout << "| Hello " << person.get_name() << " | " << person.get_role() << " view\n" ;
            cout << "[1] - View profile\n[2] - Add book\n[3] - List users\n[4] - List categories\n[5] - log out\n" ;
            cout << "| Enter your choice: " ;
            int choice ;
            cin >> choice ;
            cout << '\n' ;
            if ( cin.fail() || !( choice >= 1 && choice <= 5 ) )
            {
                  cin.clear() ;
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "\n------------------------------------------\n" ;
                  cout << "| Please enter a number in range ( 1 - 5 )! |\n" ;
                  cout << "------------------------------------------\n\n" ;
                  continue;
            }
            
            if ( choice == 1 )
            {
                  cout << "---------------\n" ;
                  cout << "Name: " << person.get_name() << "\n" << "Email: " << person.get_email() << "\n" << "Username: " << person.get_username() << "\n" << "Role: " << person.get_role() << '\n' ;
                  cout << "---------------\n\n" ;
                  continue ;
            }
            else if ( choice == 2 )
            {
                  Add_book() ;
                  continue ;
            }
            else if ( choice == 3 )
            {
                  list_users() ;
                  continue ;
            }
            else if ( choice == 4 )
            {
                  list_categories() ;
                  continue;
            }
            else  
                  return ;
      }
}
int main()
{
      add_admins() ;
      add_books_Cat() ;
      while ( true )
      {
            int id ;
            user &person = start() ;
            if ( person.get_role() == "Reader" )
                  Reader_view( person ) ;
            else
                  Admin_view( person ) ;
      }
      return 0 ;
}