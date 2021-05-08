# bubble sort 
void bSort (vector<int>)
{
	int n = 1;
	bool is swap = true;
	for(int i = 1;i<vec.size();i++)                  //i=1,i<n,i++(n-1回) 
	{
		isSwap = false;                              //起始為false 
		for(int j = 0;j<vev.size()-i;j++)            //j=0,j<n,j++ (n回)
		{
			if(vec[j]>vec[j+1])
			{
				swap(vec[j],vec[j+1]);               //交換 
				isSwap = true;                       //若交換則記錄為true 
			}
		}
		if(!isSwap)
		   break;                                    //若沒交換則跳出迴圈 
		   cout<<"The"<<n<<"th of sorting";
		   for(int i = 0;i<vec.size();i++)           //有交換才印出來 
		   {
		   	cout<<setw(3)<<vec[i];       
		   }
		   cout<<endl;
		   n++;
	}
}
