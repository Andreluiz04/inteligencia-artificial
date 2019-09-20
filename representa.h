struct Representa{
	vector <bool> cromossomo;
	//vector <int> cromossomo;
	Representa (){}
	Representa (int b){
		cromossomo.resize(b);
	}
	double getDouble(int i,int ent, int dec){
		double ans=0;
		for (int j=i+1;j<i+1+ent;j++){
			if(cromossomo[j]){
				ans+=1<<(i+ent-j);
			}
		}
		for (int j=i+1+ent;j<i+1+ent+dec;j++){
			if(cromossomo[j]){
				ans+=double(1)/(1<<(j-i-ent));
			}
		}
		if(!cromossomo[i]){
			ans*=-1;
		}
		return ans;
	}
	pair<double,double> getX(){
		double x1=getDouble(0,2,cromossomo.size()/2-1-2);
		double x2=getDouble(cromossomo.size()/2,2,cromossomo.size()/2-1-2);
		return make_pair(x1,x2);
	}
	Representa operator = (const Representa& B){
		cromossomo.resize((int)B.cromossomo.size());
		for (int i = 0 ; i < cromossomo.size(); i++){
			cromossomo[i]= B.cromossomo[i];
		}
		return (*this);
	}
	int tamano()const{
		return cromossomo.size();
	}
	bool operator == (const Representa B)const{
		int i = 0;
		while (i < cromossomo.size()){
			if (cromossomo[i] != B.cromossomo[i])
				return false;
			i++;
		}
		return true;
	}
	bool operator < (const Representa B)const{
		int i = 0;
		while (i < cromossomo.size()){
			if (cromossomo[i]< B.cromossomo[i])
				return true;
			else if (cromossomo[i]!=B.cromossomo[i])
				return false;
			i++;
		}
		return false;
	}
};
