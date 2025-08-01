#include <iostream>
using namespace std;
int main()
{
   int arr1[100];
    int n, i, max, min;
       cout<<"Enter the number of elements to be stored in the array : ";
       cin>>n;
       cout<<"Enter all "<<n<<" elements in the array : \n";
       for(i=0;i<n;i++)
            {
          cout<<"element - "<<i<<" : ";
          cin>>arr1[i];
        }
     max = arr1[0];
    min = arr1[0];
    for(i=1; i<n; i++)
    {
        if(arr1[i]>max)
        {
            max = arr1[i];
        }
        if(arr1[i]<min)
        {
            min = arr1[i];
        }
    }
    cout<<"Maximum element is : "<< max<<endl;
    cout<<"Minimum element is : "<< min;
}
