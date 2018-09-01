//empty
#include <iostream>
#include <vector>

using namespace std ;

struct nodeData 
{		
	int ownerId ;
	double val ;
	string owner_name ;		
} ;

struct Node {
	int nodeNumber ;
	double sum ;
	bool isEncrypted ;

	string nodeId, referenceNodeId , childReferenceNodeId , genesisReferenceNodeId, nodeDataHash, hashValue ;
	time_t timestamp ; 

	struct nodeData data ;
	
	vector<struct Node> childNodes ; 
	
		
} ;

int nodeCnt = 0 ;

struct Node nodeArray[1000000] ;

void printStandard()
{
	cout<<endl ;
	cout<<"1. Create a genesis node"<<endl ;
	cout<<"2. Create set of child nodes of a particular Node"<<endl ;
	cout<<"3. Create a child node that originates from a particular Node"<<endl ;
	cout<<"4. Encrypt"<<endl;
	cout<<"5. TErminate"<<endl ;
	cout<<endl ;
}

struct Node inputNode( string ref_id , string gen_ref_id  )
{
	struct Node temp ; 
	struct nodeData tempData ;
	
	// kind of default 
	temp.timestamp = clock() ;
	temp.sum = 0.0 ;
	temp.isEncrypted = false ;
	
	cout<<endl ;
	cout<<"enter details :  "<<endl ;
	cout<<"owner name : " ; cin>>tempData.owner_name ;
	cout<<"owner Id : " ; cin>>tempData.ownerId ;
	cout<<"Value : " ; cin>>tempData.val ;
	cout<<endl ;
	
	temp.data = tempData ;
	temp.nodeNumber = nodeCnt ; 
	temp.nodeId = to_string(nodeCnt) ;
	temp.referenceNodeId = ref_id ;
	temp.childReferenceNodeId = "" ;
	temp.genesisReferenceNodeId = gen_ref_id ;
	
	return temp ;
	
}

// bool printverify(string password,string algo)
// {
//         string password1=encrypt(password);
//         string algo1=encrypt("qwerty");

//         map<int,struct node*>::iterator it=all.begin();
//         int flag=0;

//         for(;it!=all.end(); it++)
//         {
//             if(it->second->data->password==password1 && it->second->data->algo==algo1)
//             {
//                 flag=1;

//                 cout<<encrypt(it->second->data->address)<<endl;
//                 cout<<encrypt(it->second->data->phone)<<endl;
//                 cout<<encrypt(it->second->data->mobile)<<endl;
//                 cout<<encrypt(it->second->data->name)<<endl;

//                 break;
//             }
//         }

//         if(flag==1)
//         return true;

//         return false;
// }

void printNode(int ind)
{
	cout<<"Time Stamp : "<<nodeArray[ind].timestamp<<endl ;
	cout<<"Node Number : "<<nodeArray[ind].nodeNumber<<endl ;
	cout<<nodeArray[ind].nodeId<<" "<<nodeArray[ind].referenceNodeId<<" "<<nodeArray[ind].childReferenceNodeId<<" "<<nodeArray[ind].genesisReferenceNodeId<<endl ;
	cout<<"sum :"<<nodeArray[ind].sum<<endl ;
	
	cout<<"data : "<<nodeArray[ind].data.val<<endl ;
}

void printNodeDetails()
{
	cout<<endl ;
	for (int i=0;i<nodeCnt;i++)
	{
		cout<<"Details"<<i<<" : "<<endl ;
		printNode(i) ; 
	}
}

int main()
{	
	int choice ; 
	
	while (1)
	{
		
		printStandard() ;
		
		cout<<"Enter Your Choice : " ;
		cin>>choice ;
		cout<<endl ;
		
		if (choice < 1 || choice > 5)
		{
			cout<<"wrong Choice"<<endl ;

		}else if (choice == 5)
		{ 
			break ;
		}else if ( choice == 1)
		{
			
			// Adding a genesis Node 
			
			struct Node newnode = inputNode( "" , to_string(nodeCnt) ) ;
			
			nodeArray[nodeCnt] = newnode ; 
			nodeCnt++ ;
			
			cout<<"Created! with Node number = "<<(nodeCnt-1)<<endl ;
			
			printNodeDetails() ; 
			
		}else if (choice == 2)
		{
			
			// adding child nodes of a particular Node
			
			int nodeNo, child_nodes ; 
			
			cout<<"Enter node Number for its child: " ; cin>>nodeNo ; 
			
			if (nodeNo >= nodeCnt)
			{
				cout<<nodeNo<<" not valid"<<endl ;
				continue ;
			}
			
			cout<<"enter no of child: " ; cin>>child_nodes ; 
			
			vector<struct Node> nodes ; 
			double tempSum = 0.0 ; 
			
			for (int i=1 ; i<= child_nodes ; i++)
			{
				cout<<"Details "<<i<<" : "<<endl ;
				struct Node newnode = inputNode( nodeArray[nodeNo].nodeId , nodeArray[nodeNo].genesisReferenceNodeId ) ;
				nodes.push_back(newnode) ; 
				
				tempSum += newnode.data.val ; 
				
			}
			
			if ( tempSum + nodeArray[nodeNo].sum > nodeArray[nodeNo].data.val )
			{
				cout<<"Error - property not followed"<<endl ; 
				continue ;
			}
			
			for (auto itr : nodes)
			{
				itr.nodeId = to_string(nodeCnt) ; 
				itr.nodeNumber = nodeCnt ; 
				nodeArray[nodeCnt] = itr ; 
				nodeCnt++ ; 
				
				nodeArray[nodeNo].sum += itr.data.val ;
				nodeArray[nodeNo].childReferenceNodeId += ( itr.nodeId + "/" ) ; 
				nodeArray[nodeNo].childNodes.push_back(itr) ; 
			}
			
					
		}else if (choice == 3)
		{
			int nodeNo ; 
			cout<<"Enter the Node number of the parent Node : " ; cin>>nodeNo ;
			
			if (nodeNo >= nodeCnt)
			{
				cout<<nodeNo<<" is not a valid number"<<endl ;
				continue ;
			}
			
			double tempSum = 0.0 ; 
			
			cout<<"Details of child node "<<endl ;
			struct Node newnode = inputNode( nodeArray[nodeNo].nodeId , nodeArray[nodeNo].genesisReferenceNodeId ) ;
			tempSum += newnode.data.val ; 
			
			if ( tempSum + nodeArray[nodeNo].sum > nodeArray[nodeNo].data.val )
			{
				cout<<"Error! property not followed"<<endl ; 
				continue ;
			}
			
			nodeArray[nodeCnt] = newnode ; 
			nodeCnt++ ;
			
			nodeArray[nodeNo].sum += newnode.data.val ;
			nodeArray[nodeNo].childReferenceNodeId += ( newnode.nodeId + "/" ) ; 
			nodeArray[nodeNo].childNodes.push_back(newnode) ; 
			
			
			
		}
		else if(choice==4){
			string password,algo;
            cout<<"Enter password and algo key";

            //bool k=printverify(password,algo);
		}
		
	}
	
	return 0 ;
}
