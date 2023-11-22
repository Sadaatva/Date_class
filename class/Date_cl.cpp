#include <iostream>

struct DateExceptionsY{
    int years;
};

struct DateExceptionsM{
    int months;
};

struct DateExceptionsD{
    int days;
};
	
static bool Year4(int years){
        return (years % 4 == 0 && (years % 100 != 0 || years % 400 == 0));
}
    
class Date{
private:
    int years;
    int months;
    int days;

public:
   Date(int years, int months, int days) : years(years), months(months), days(days){

	int days_m[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 0 для индексов месяцев
        
        if(months == 2 && Year4(years)){
            days_m[2] = 29;
        } 
		
	if(years <= 0){
	  throw DateExceptionsY(years);
	}
		
	if(months <= 0 || months > 12){
	  throw DateExceptionsM(months);
	}
		
	if(days <= 0 || days > days_m[months]){
	  throw DateExceptionsD(days);
	}
   }
    Date(int days) : years(1), months(1), days(days){
	int days_m[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		
	if(days <= 0 || days > days_m[months]){
	  throw DateExceptionsD(days);
	}
   }
	
    int GetYears() const;
    int GetMonths() const;
    int GetDays() const;
	
    Date& operator += (int d){
        days += d;
        return *this;
    }
    
    Date operator+ (int d)const{
	int days_pm = days + d;
        return Date(years, months, days_pm);
    }
    
    Date operator- (int d)const{
	int days_pm = days - d;
        return Date(years, months, days_pm);
    }
        
    void AddDays(int d){
	days += d;
	Date(years, months, days);
	}
};

std::ostream& operator << (std::ostream& out, const Date& d){
    out << d.GetYears() << " : " << d.GetMonths() << " : " << d.GetDays();
    return out;
}

std::istream& operator >> (std::istream& in, Date& d){
	
    std::cin.exceptions(std::istream::failbit);
	
    int ys;
    int ms;
    int ds;
    char c;
    
    in >> ds >> c;
    in >> ms >> c;
    in >> ys;
    
    d = Date(ys, ms, ds);
    return in;
}

int Date::GetYears() const{
    return years;
}

int Date::GetMonths() const{
    return months;
}

int Date::GetDays() const{
    return days;
}


         
int main(){
  Date d(0, 4, 20);
  std::cout << "Date: " << d << "\n";
  
  d.AddDays(-22);
  std::cout << "Next: " << d << "\n";
  
  return 0;
}
