struct C_Proc{
	int Sum;
	int Sum_Min;
	C_Proc(int s){
		Sum_Min=s;
		Sum=0;
	}
	bool Get_Stat()
	{
		if(Sum >= Sum_Min) return true;
		return false;
	}
	void Reset()
	{
		Sum=0;
	}
};
struct B_Proc{
	bool State;
	int Sum;
	int Sum_Min;
	int *Mass_W;
	int Max_num;
	int num;
	C_Proc **Mass;
	B_Proc(int a, int s){
		State=0;
		Sum_Min=s;
		Max_num=a;
		num=0;
		Mass_W=new int[a];
		Mass=new C_Proc*[a];
	}
	void Add_C(int w){
		if(num<Max_num){
			Mass[num]=new C_Proc(3);
			Mass_W[num]=w;
			num++;
		}
	}
	void Add_C(C_Proc *a,int w){
		if(num<Max_num){
			Mass[num]=a;
			Mass_W[num]=w;
			num++;
		}
	}
	void Reset()
	{
		Sum=0;
	}
	void Count_State()
	{
		if(Sum>=Sum_Min) State=true;
		else State=false;
	}
	void Count_C(){
		Count_State();
		if(!State) return;
		for(int i=0;i<num;i++)
		{
			Mass[i]->Sum+=Mass_W[i]*Sum;
		}
	}
};
struct A_Proc{
	int State;
	int *Mass_W;
	B_Proc **Mass;
	int Max_num;
	int num;
	A_Proc(int a, int s){
		State=0;
		Max_num=a;
		num=0;
		Mass_W=new int[a];
		Mass=new B_Proc*[a];
	}
	void Add_B(int w){
		if(num<Max_num){
			Mass[num]=new B_Proc(50000,5);
			Mass_W[num]=w;
			num++;
		}
	}
	void Add_B(B_Proc *a,int w){
		if(num<Max_num){
			Mass[num]=a;
			Mass_W[num]=w;
			num++;
		}
	}
	void Count_B(){
		for(int i=0;i<num;i++){
			Mass[i]->Sum+=Mass_W[i]*State;
		}
	}
};
struct Perceptron{
	int num_A;
	int num_B;
	int num_C;
	int Max_num_A;
	int Max_num_B;
	int Max_num_C;
	bool *c_stats;
	A_Proc **Mass_A;
	B_Proc **Mass_B;
	C_Proc **Mass_C;
	Perceptron(int a, int b, int c){
		Max_num_A=a;
		Max_num_B=b;
		Max_num_C=c;
		num_A=0;
		num_B=0;
		num_C=0;
		Mass_A=new A_Proc*[a];
		Mass_B=new B_Proc*[b];
		Mass_C=new C_Proc*[c];
		c_stats=0;
	}
	void New_C(int w){
		if(num_C<Max_num_C){
			Mass_C[num_C]=new C_Proc(w);
			num_C++;
		}
	}
	void New_B(int w){
		if(num_B<Max_num_B){
			Mass_B[num_B]=new B_Proc(50000,w);
			num_B++;
		}
	}
	void New_A(){
		if(num_A<Max_num_A){
			Mass_A[num_A]=new A_Proc(50000,10);
			num_A++;
		}
	}
	void New_C_Mass(int a){
		for(int i=0;i<a;i++)
		{
			New_C(5);
		}
	}
	void New_B_Mass(int a){
		for(int i=0;i<a;i++)
		{
			New_B(5);
		}
	}
	void New_A_Mass(int a){
		for(int i=0;i<a;i++)
		{
			New_A();
		}
	}

	void New_A_to_B()
	{
		for(int i=0;i<num_A;i++)
		{
			for(int j=0;j<num_B;j++)
			{
				Mass_A[i]->Add_B(Mass_B[j],1);
			}
		}
	}

	void New_B_to_C()
	{
		for(int i=0;i<num_B;i++)
		{
			for(int j=0;j<num_C;j++)
			{
				
				Mass_B[i]->Add_C(Mass_C[j],1);
			}
		}
	}

	void Count(){
		for(int i=0;i<num_B;i++)
		{
			Mass_B[i]->Reset();
		}
		for(int i=0;i<num_C;i++)
		{
			Mass_C[i]->Reset();
		}
		for(int i=0;i<num_A;i++)
		{
			Mass_A[i]->Count_B();
		}
		for(int i=0;i<num_B;i++)
		{
			Mass_B[i]->Count_C();
		}
		if(c_stats!=0)delete(c_stats);
		c_stats=new bool[num_C];
		for(int i=0;i<num_C;i++)
		{
			c_stats[i]=Mass_C[i]->Get_Stat();
		}
	}
	void New_State(int *a){
		for(int i=0;i<num_A;i++)
		{
			Mass_A[i]->State=a[i];
		}
	}
	void Save(char *name)
	{
		FILE* in=fopen(name, "w");
		fprintf(in,"%d %d %d %d %d %d\n\n", Max_num_A, num_A, Max_num_B, num_B, Max_num_C, num_C);
		for(int i=0;i<num_A;i++)
		{
			for(int j=0;j<Mass_A[i]->num;j++)
			{
				fprintf(in,"%d ", Mass_A[i]->Mass_W[j]);
			}
			fprintf(in,"\n");
		}
		fprintf(in,"\n");
		fprintf(in,"\n");
		for(int i=0;i<num_B;i++)
		{
			for(int j=0;j<Mass_B[i]->num;j++)
			{
				fprintf(in,"%d ", Mass_B[i]->Mass_W[j]);
			}
			fprintf(in,"\n");
		}
		fprintf(in,"\n");
		for(int i=0;i<num_B;i++)
		{
			fprintf(in,"%d ",Mass_B[i]->Sum_Min);
		}
		fprintf(in,"\n");
		for(int i=0;i<num_C;i++)
		{
			fprintf(in,"%d ",Mass_C[i]->Sum_Min);
		}
		fprintf(in,"\n");
		fprintf(in,"\n");
		fclose(in);
	}
	void Load(char *name)
	{
		FILE* in=fopen(name, "r");
		int nm;
		int na,nb,nc;
		fscanf(in,"%d %d %d %d %d %d", &Max_num_A, &na, &Max_num_B, &nb, &Max_num_C, &nc);
		New_A_Mass(na);
		New_B_Mass(nb);
		New_C_Mass(nc);
		New_A_to_B();
		New_B_to_C();
		for(int i=0;i<num_A;i++)
		{
			for(int j=0;j<Mass_A[i]->num;j++)
			{
				fscanf(in,"%d ", &nm);
				Mass_A[i]->Mass_W[j]=nm;
			}
		}
		for(int i=0;i<num_B;i++)
		{
			for(int j=0;j<Mass_B[i]->num;j++)
			{
				fscanf(in,"%d ", &nm);
				Mass_B[i]->Mass_W[j]=nm;
			}
		}
		for(int i=0;i<num_B;i++)
		{
			fscanf(in,"%d ", &nm);
			Mass_B[i]->Sum_Min=nm;
		}
		for(int i=0;i<num_C;i++)
		{
			fscanf(in,"%d ", &nm);
			Mass_C[i]->Sum_Min=nm;
		}
		fclose(in);
	}
	void learn(int *st)
	{
		//printf("Hi me");
		bool *state=new bool[num_C];
		for(int i=0;i<num_C;i++)
		{
			//printf("		(%d) - %d", i, st[i]);
			state[i]=st[i];
		}
		for(int i=0;i<num_C;i++)
		{
			if(state[i]!=c_stats[i])
			{
				if(!state[i])
				{
					for(int j=0;j<num_B;j++)
					{
						if(Mass_B[j]->State)Mass_B[j]->Mass_W[i]-=1;
					}
				}
				else if(state[i])
				{
					for(int j=0;j<num_B;j++)
					{
						if(Mass_B[j]->State)Mass_B[j]->Mass_W[i]+=1;
					}
				}
			}
		}
	}
};