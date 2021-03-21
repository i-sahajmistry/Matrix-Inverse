#include<iostream>
#include<vector>

using namespace std;

/************************************ToREF***********************************************/


class ToREF
{
protected:
    int n, m;
    vector<vector<float>> matrix;
    vector<vector<float>> inverse;
    vector<pair<int, int>> pivote;
    pair<int, int> lastPivote;
public:
    void setMatrix();
    void findNextPivote();
    void takePivoteRowAbove(pair<int, int>);
    void makeBelowPivoteZero(pair<int, int>);
    void makeREF();
    void display();
};


/************************************ToRREF***********************************************/



class ToRREF : public ToREF
{
public:
    void makeAbovePivoteZero(pair<int, int>);
    void makeRREF();
};

/************************************Int Main**********************************************/

int main()
{
    ToRREF a;
    a.setMatrix();
    a.makeRREF();
    a.display();
    return 0;
}

/************************************Defining Function of ToREF*****************************/


void ToREF :: setMatrix()
{
    cout << "Enter size of square matrix : ";
    cin >> n;
    m = n;
    cout << "Enter Matrix element : " << endl;
    for(int i = 0; i < n; i++)
    {
        vector<float> temp1;
        vector<float> temp2;
        float x;
        for(int j = 0; j < m; j++)
        {            
            cin >> x;
            temp1.push_back(x);
            temp2.push_back((i==j ? 1 : 0));
        }
        matrix.push_back(temp1);
        inverse.push_back(temp2);
    }  
}


void ToREF :: findNextPivote()
{
    cout << "Find next pivote" << endl;
    int x = pivote.size();
    bool gotPivote = false;
    if(x == 0)
    {
        for(int i = 0; i < m; i++)
        {
            bool flag = false;
            for(int j = 0; j < n; j++)
            {
                if(matrix[j][i] != 0)
                {
                    pivote.push_back(make_pair(j, i));
                    lastPivote = make_pair(j, i);
                    gotPivote = true;
                    flag = true;
                    break;
                }
            }
            if(flag == true) { break; }
        }
    }

    else
    {
        int a = pivote[x-1].second; 
        int b = pivote[x-1].first;
        if(a < m);
        {
            for(int i = a + 1; i < m; i++)
            {
                bool flag = false;
                for(int j = b + 1; j < n; j++)
                {
                    if(matrix[j][i] != 0)
                    {
                        pivote.push_back(make_pair(j, i));
                        lastPivote = make_pair(j, i);
                        gotPivote = true;
                        flag = true;
                        break;
                    }
                }
                if(flag == true) { break; }
            }
        }
    }
    if(gotPivote == false)
    {
        lastPivote = make_pair(n, m);
    }
    if(lastPivote.first != n)
        cout << "Pivote : (" << lastPivote.first + 1 << ", " << lastPivote.second + 1 << ")"<< endl << endl;
    else
    {
        cout << "No more pivotes..." << endl << endl;
        cout << "****REF Matrix****" << endl;
        display();
    }
}

void ToREF :: takePivoteRowAbove(pair<int, int> p)
{
    cout << "Take pivote row above" << endl << endl;
    int rowNo1 = pivote.size() - 1;
    int rowNo2 = p.first;

    cout << "R" << rowNo1+1 << " <-> R" << rowNo2+1 << endl; 

    for(int i = 0; i < m; i++)
    {
        float temp1 = matrix[rowNo1][i];
        float temp2 = inverse[rowNo1][i];

        matrix[rowNo1][i] = matrix[rowNo2][i];
        inverse[rowNo1][i] = inverse[rowNo2][i];
        
        matrix[rowNo2][i] = temp1;
        inverse[rowNo2][i] = temp2;
    }

    lastPivote = make_pair(rowNo1, p.second);
    pivote[rowNo1] = make_pair(rowNo1, p.second);
    display();
}

void ToREF :: makeBelowPivoteZero(pair<int, int> p)
{
    cout << "Make elements below pivote zero" << endl << endl;
    float a = matrix[p.first][p.second];
    cout << "R" << p.first+1 << " --> R" << p.first+1 << " / " << a << endl; 
    for(int i = 0; i < m; i++)
    {
        matrix[p.first][i] /= a;
        inverse[p.first][i] /= a;
    }

    for(int i = p.first + 1; i < n; i++)
    {
        float b = matrix[i][p.second];
        cout << "R" << i+1 << " --> R" << i+1 << " - (R" << p.first+1 << " * " << b << ")" << endl; 
        for(int j = 0; j < m; j++)
        {
            matrix[i][j] -= (b * matrix[p.first][j]);
            inverse[i][j] -= (b * inverse[p.first][j]);
        }

    }
    display();
}

void ToREF :: display()
{
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(matrix[i][j] != (-0))
                cout << matrix[i][j] << " "; 
            else
                cout << 0 << " ";
        }

        cout << "| ";

        for(int j = 0; j < m; j++)
        {
            if(inverse[i][j] != (-0))
                cout << inverse[i][j] << " "; 
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void ToREF :: makeREF()
{
    cout << endl <<"Convert to REF" << endl;

    do
    {
        findNextPivote();
        if(lastPivote.first != n)
        {
            takePivoteRowAbove(lastPivote);
            makeBelowPivoteZero(lastPivote);
        }
    }while(lastPivote.first != n);
}


/************************************Defining Function of ToRREF*****************************/

void ToRREF :: makeAbovePivoteZero(pair<int, int> p)
{
    cout << "Make all elements above pivote zero" << endl;
    for(int i = 0; i < p.first; i++)
    {
        float b = matrix[i][p.second];
        cout << "R" << i+1 << " --> R" << i+1 << " - (R" << p.first+1 << " * " << b << ")" << endl; 
        for(int j = 0; j < m; j++)
        {
            matrix[i][j] -= (b * matrix[p.first][j]);
            inverse[i][j] -= (b * inverse[p.first][j]);
        }
    }
    display();
}

void ToRREF :: makeRREF()
{
    makeREF();
    for(int i = pivote.size() - 1; i >= 0; i--)
    {
        makeAbovePivoteZero(pivote[i]);
    }
    cout << "****RREF Matrix****" << endl;
}