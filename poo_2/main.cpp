#include <iostream>
#include<conio.h>
#include<string.h>
#include<fstream>

using namespace std;

class Nod{
    int info;
    Nod* next;
public:
    Nod(){next=0;};//constructor implicit
    Nod(int info,Nod* next=0);//de initializare
    int getInfo();//da info
    int setInfo(int info);//seteaza info
    Nod* getNext();
    void setNext(Nod* next);
    int operator = (Nod &n);
    int operator != (Nod &n);
    friend class coada;
    friend class PriorityQueue;
    friend istream& operator>>(istream& t, Nod &n);
    friend ostream& operator<<(ostream& v, Nod &n);
};
/*constructor de initializare*/
Nod::Nod(int info,Nod* next)
{
    this->info=info;
    this->next=next;
}

int Nod::getInfo()
{
    return info;
}

int Nod::setInfo(int info)
{
    this->info=info;
}

Nod* Nod::getNext()
{
    return next;
}
void Nod::setNext(Nod* next)
{
    this->next=next;
}

int Nod::operator =(Nod &n)
{
    return this->info==n.info;
}

int Nod::operator !=(Nod &n)
{
     if(this->info != n.info)
        return true;
     else return false ;
}

istream& operator>>(istream& t, Nod &n){
    cout<<"Citeste info la nod : ";
    t>>n.info;
    return t;
}

ostream& operator<<(ostream& v, Nod &n){
    v<<n.info<<" ; ";
    return v;
}

class coada
{
    Nod* prim;
    Nod* ultim;
public:
    coada();//constructor
    ~coada();//destructor
    int isEmpty() ;//coada vida
    Nod* getFirst() const;//da nodul prim
    Nod* getLast() const ;
    Nod* setFirst(Nod* prim);
    Nod* setLast(Nod* last);
    int top();//afiseaza primul element din coada
    void push (Nod n);//adaugare
    void push_in (Nod n);
    void pop ();
    void pop_sf();
    int get_count();
    coada operator - ( coada& c);
    coada operator + ( coada &c);
    bool operator == (coada &coada);
    coada copie();
    bool identic(Nod *n1,Nod* n2);
    friend class PriorityQueue;
    friend ostream& operator<<(ostream& out, coada&);
    friend istream& operator>>(istream& in, coada&);
};

coada::coada()//constructor
{
    prim=ultim=NULL;
}

coada::~coada()//destructor
{
    Nod* p=prim;
    Nod*q;
    while(p!=0)
    {
        q=p;
        p=p->next;
        delete q;
    }
    prim=ultim=NULL;
}

int coada::isEmpty() //coada goala
{
    return prim==0;
}

int coada::get_count()
{
	Nod *p = prim;
	int s = 0;
	while (p != NULL)
	{
		s++;
		p = p->next;
	}
	cout<<"nr este : "<<s;
	return s;
}

void coada::push(Nod n)//adaugare nod
{
    Nod *p;
    p=new Nod(n.info,0);
    if(isEmpty())
        prim=ultim=p;
    else {
        ultim->next=p;
        ultim=p;
    }
}

void coada::push_in(Nod n)
{
    Nod *p;
    p=new Nod(n.info,0);
    p->next=prim;
    prim=p;
}

void coada::pop ()
{
    int X;
    Nod *p;
    p= new Nod();
    if (prim == 0) // Underflowy
                cout<<"goala";
    else
    {
        //extragerea valorii, cu eliberarea spatiului care a fost ocupat de nodul Front
        X = prim -> info;
        p = prim;
        prim = prim -> next;
        delete p  ;
        if (prim == NULL) // coada avea un singur element, iar acum e vidã
            ultim = NULL;
    }
}

void coada::pop_sf()
{
    Nod*r;
    for(r = prim;r->next->next;r=r->next);
    Nod *t=t->next;
    r->next = NULL;
    ultim = r;
    delete t;
    if (prim == NULL) // coada avea un singur element, iar acum e vidã
            ultim = NULL;
}


Nod* coada::getFirst() const{
     return prim;
    }


Nod* coada::getLast() const {
     return ultim;
    }


Nod* coada::setFirst(Nod* prim)
{
    this->prim = prim;
}

Nod* coada::setLast(Nod* last)
{
    this->ultim = last;
}
//afiseaza primul element din coada
int coada::top(){
    Nod * p= getFirst();
    cout<<p->getInfo();
     return 0;
    }

ostream& operator<<(ostream& out, coada& coada){
 Nod * p=coada.prim;
        while(p!=NULL){
            out<<p->getInfo()<<",";
            delete p;
            p=p->getNext();
            }
        cout<<"\b ";
        delete p;
        return out;
}


istream& operator>>(istream& r, coada& coada){
    int numar_noduri;
    cout<<"da numarul de noduri: ";
    r>>numar_noduri;
    for(int i=0;i<numar_noduri;i++)
    {
        cout<<"da info : ";
        int info ;
        r >> info;
        coada.push(info);
    }
    return r;
}

coada coada::operator - (coada& c)
{
    if(identic(c.prim,this->prim) == 0)
    {
        c.pop();
        this->pop();
    }

    return *this;
}

coada coada::copie()
{
    coada c;
    Nod* p=this->prim;
    while(p!=0)
    {
        c.push(p->info);
        p=p->next;
    }
    return c;
}

coada coada::operator + (coada& c)
{
    coada t = this->copie();
    Nod *p = c.prim;
    while(p!=0)
    {
        t.push(p->info);
        p=p->next;
    }
    return t;
}
//am creat functia identic petru a compara nodurile si a trece la urmatoarele
bool coada::identic(Nod *n1, Nod *n2)
{
    if(n1==NULL && n2==NULL)
        return true ;
    else {
        if(n1==NULL || n2==NULL)
            return false;
        if(n1->info == n2->info)
            return identic(n1->next,n2->next);
        else return false ;
    }
}

bool coada::operator ==(coada &coada)
{
    if(identic(this->getFirst(),coada.getFirst()))
       return true;
    else return false;
}


class DEQUE:public coada, public Nod
{
public:
    DEQUE(){};
    ~DEQUE(){};
    virtual void push_d(int val , int alegere)
    {
        cout<<"Alegere : 1 . La inceput \n 2. La sfarsit \n ";
      if(alegere == 1)
      {
           push_in(Nod(val));
           cout<<"Am pus ";
      }

      else if(alegere == 2 )
      {
                   push(Nod(val));
                   cout<<"Am pus ";
      }
        else cout<<"Alegere invalida";
    }

    virtual void pop_d(int alegere)
    {
        cout<<"Alegere : \n 1.Sterge inceput : \n 2. Sterge sfarsit :";
        if(alegere == 1){
            pop();
            cout<<"Sters";
        }

        else if(alegere == 2)
        {
            pop_sf();
            cout<<"Sters";
        }

        else cout<<"Alegere invalida ";
    }

};


class PriorityQueue:public coada, public Nod
{
    int prioritate;
public:
    PriorityQueue(){};
    ~PriorityQueue(){};
    void displayPQ() {
       Nod *ptr;
       ptr = prim;

       if (prim == NULL)
       cout<<"Priority Queue is empty\n";

       else {
          cout<<"Queue elements in decreasing priority are :\n";
          while(ptr != NULL) {
             cout<<ptr->info<<" ";
             ptr = ptr->next;
          }
          cout<<endl;
       }
}
    void push_p(int val, int prioritate)
    {
        this->prioritate = prioritate;
        cout<<"AVem si prioritate \n";
        push(Nod(val));
        cout<<"Am pus \n";
    }

    void pop_p(){
        Nod *temp;

       if(prim == NULL)
       cout<<"Priority Queue Underflow\n";

       else {
          temp = prim;
          cout<<"Deleted item is: "<<temp->info<<endl;
          prim = prim->next;
          delete(temp);
   }

}
};



int main()
{

coada c1,c2;
DEQUE c3;
/*c1.push(Nod(2));
c1.push(Nod(3));
c1.push(Nod(4));
c2.push(Nod(2));
c2.push(Nod(3));
//c2.pop();
cout<<"Afisare coada c2 :"<<c2;
cout<<'\n';
cout<<"Primul element din coada  c1 : "<<*c1.getFirst()<<"\nUltimul element din coada c1 : "<<*c1.getLast();
cout<<'\n';
//am avut de construit operatorul == care compara doua cozi
cout<<"Sunt cozile c1 si c2 egale ? \n";
if(c1==c2)
    cout<<"Egale \n";
else
    cout<<"Nu sunt egale \n";

//coada rez;
//rez=c1-c2;
//cout<<"Coada stearsa :"<<rez;
//cout<<'\n';
cout<<"coada concatenata : ";
coada rezultat;
rezultat=c2+c1;
cout<<rezultat;
c1.push(Nod(2));
c1.push(Nod(3));
cout<<c1;
c1.pop_sf();
cout<<c1;*/
c3.push_d(2,2);
c3.push_d(3,1);
c3.pop_d(1);
PriorityQueue c4;
c4.push_p(3,2);
c4.push_p(1,1);
c4.displayPQ();
return 0;
}
