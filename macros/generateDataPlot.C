{
    
        gROOT->ProcessLine(".x /home/t2k/cvson/rootlogon.C");
        gROOT->ProcessLine(".L /home/t2k/cvson/basicPlotUtil.C");
        
        gROOT->ProcessLine(".L baseTree.cc");
        
        baseTree *pAnalysis = new baseTree();
        pAnalysis->MakeDataPlot("/home/t2k/cvson/gpfs/ingrid/backup/dataProcess/fix20150420/data_merged_ccqe_addpidFFnew.root","databasicPlot.root");
        cout<<"Processing sucessfully"<<endl;
    
}