# CGTU-Huffman-coder-decoder
void CreatHuffmanTree(HuffmanTree &HT,int n) 
{
    int s1,s2;
    if(n<=1)
        return;
    int m=2*n-1;  //当n大于1时，n个叶子结点需要2*n-1个结点
    HT=new HTNode[m+1];  //0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根结点
    //将1~m号单元中的双亲、左孩子，右孩子的下标都初始化为0
    for(int i=1; i<=m; ++i) 
	{
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    cout<<"请输入叶子结点的权值：";
    //输入前n个单元中叶子结点的权值
    for(int i=1; i<=n; ++i) 
	{
        cin>>HT[i].weight;
    }
    //通过n-1次的选择、删除、合并来创建哈夫曼树
    for(int i=n+1; i<=m; ++i) 
	{
        //在HT[k](1≤k≤i-1)中选择两个其双亲域为0且权值最小的结点，并返回它们在HT中的序号s1和s2
        Select(HT,i-1,s1,s2);
        //得到新结点i，从森林中删除s1，s2，将s1和s2的双亲域由0改为i
        HT[s1].parent=i;
        HT[s2].parent=i;
        //s1,s2分别作为i的左右孩子
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        //i的权值为左右孩子权值之和
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
}

