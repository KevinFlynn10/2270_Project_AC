#include <iostream>
#include <fstream>
#include "SNP_Fun.h"

SNP_Fun::SNP_Fun()
{
    //ctor
}

SNP_Fun::~SNP_Fun()
{
    //dtor
}

int SNP_Fun::hashRSID(std::string id, int hashSize)
{
    int sum = 0;

    for(int i = 0; i < id.length(); i++)
    {
        sum = sum + id[i];
    }

    sum = sum % hashSize;

    return sum;
}

int SNP_Fun::getGenoInt(std::string geno)
{
    int genoInt = geno[0] + geno[1];

    switch(genoInt)
    {
    case 130:
        return 0;
    case 132:
        return 1;
    case 136:
        return 2;
    case 149:
        return 3;
    case 134:
        return 4;
    case 138:
        return 5;
    case 151:
        return 6;
    case 142:
        return 7;
    case 155:
        return 8;
    case 168:
        return 9;
    default:
        std::cout << "Invalid Genotype" << '\n';
    }

    return -1;
}

void SNP_Fun::default_add_rsid(RSID* rsid_obj, std::string effect)
{
    int genoInt = getGenoInt(rsid_obj->genotype); //Gets the integer value of the genotype string
    int idInt = hashRSID(rsid_obj->id, 10); //Gets the hashed value of the RSID string
    rsid_obj->info = effect; //Sets the effect of the rsid

    if(GC_Table[genoInt][rsid_obj->chromosome].empty()) //If a vector doesn't in the gene/chrom position create one and add RSID
    {
        std::vector<RSID*> rsid_Table (10);
        GC_Table[genoInt][rsid_obj->chromosome] = rsid_Table;

        GC_Table[genoInt][rsid_obj->chromosome][idInt] = rsid_obj;
    }
    else
    {
        //std::cout << genoInt << ":" << rsid_obj->chromosome << ":" << idInt << '\n';

        if(GC_Table[genoInt][rsid_obj->chromosome][idInt] == NULL)
        {
            GC_Table[genoInt][rsid_obj->chromosome][idInt] = rsid_obj;
        }
        else
        {

            RSID *temp = GC_Table[genoInt][rsid_obj->chromosome][idInt];

            if(stoi(temp->id.substr(2, temp->id.length())) > stoi(rsid_obj->id.substr(2, rsid_obj->id.length())))
            {
                rsid_obj->next = temp;

                GC_Table[genoInt][rsid_obj->chromosome][idInt] = rsid_obj;
            }
            else
            {

                while(temp->next != NULL && (stoi(rsid_obj->id.substr(2, rsid_obj->id.length())) > stoi(temp->next->id.substr(2, temp->id.length()))))
                {
                    temp = temp->next;
                }

                if(temp->next != NULL)
                {

                    rsid_obj->next = temp->next;
                    temp->next = rsid_obj;
                }

                else
                {
                    temp->next = rsid_obj;
                }
            }
        }
    }
}

void SNP_Fun::user_add_rsid(RSID* rsid_obj)
{
    int genoInt = getGenoInt(rsid_obj->genotype); //Gets the integer value of the genotype string
    int idInt = hashRSID(rsid_obj->id, 10); //Gets the hashed value of the RSID string

    if(GC_Table[genoInt][rsid_obj->chromosome].empty()) //If a vector doesn't in the gene/chrom position create one and add RSID
    {
        std::vector<RSID*> rsid_Table (10);
        GC_Table[genoInt][rsid_obj->chromosome] = rsid_Table;

        GC_Table[genoInt][rsid_obj->chromosome][idInt] = rsid_obj;
    }
    else
    {
        //std::cout << genoInt << ":" << rsid_obj->chromosome << ":" << idInt << '\n';

        if(GC_Table[genoInt][rsid_obj->chromosome][idInt] == NULL)
        {
            GC_Table[genoInt][rsid_obj->chromosome][idInt] = rsid_obj;
        }
        else
        {

            RSID *temp = GC_Table[genoInt][rsid_obj->chromosome][idInt];

            if(stoi(temp->id.substr(2, temp->id.length())) > stoi(rsid_obj->id.substr(2, rsid_obj->id.length())))
            {
                rsid_obj->next = temp;

                GC_Table[genoInt][rsid_obj->chromosome][idInt] = rsid_obj;
            }
            else
            {

                while(temp->next != NULL && (stoi(rsid_obj->id.substr(2, rsid_obj->id.length())) > stoi(temp->next->id.substr(2, temp->id.length()))))
                {
                    temp = temp->next;
                }

                if(temp->next != NULL)
                {

                    rsid_obj->next = temp->next;
                    temp->next = rsid_obj;
                }

                else
                {
                    temp->next = rsid_obj;
                }
            }
        }
    }
}

void SNP_Fun::createMatrix(std::string filename)
{
    std::string token;
    std::ifstream infile;
    infile.open(filename.c_str());


    int counter = 0;
    int column = 0;

        while (!infile.eof())
    {

        std::string rsId;
        std::string Chrom;
        std::string pos;
        std::string genotype_in;
        int Chromosome_in = 0;
        int position_in = 0;

        getline(infile, rsId, ' ');
        getline(infile, Chrom, ' ');
        getline(infile, pos, ' ');
        getline(infile, genotype_in);
        Chromosome_in = stoi(Chrom);
        position_in = stoi(pos);

        RSID *temp = sort_Data(rsId, Chromosome_in, position_in, genotype_in);

    }

}

 RSID* SNP_Fun::sort_Data(std::string rsid_str, int chromosome1, int position1, std::string genotype1)
 {
        RSID *rsID = new RSID;// creates a new instance of the struct
        rsID->id = rsid_str; //sets the id variable
        rsID->chromosome = chromosome1;//sets the chromosome variable for this instance
        rsID->position = position1;// sets the position variable for this instance
        rsID->genotype = genotype1;// sets the genotype variable for this instance

        return rsID;

 }

/*void SNP_Fun::place_in(RSID* temp)
{
    int geno_sum = hashGeno(temp->genotype);
    for (int i=0;i<CHROM;i++)
    {
        if (i == temp->chromosome)
        {
            if (GC_Table[geno_sum][i] == NULL)
            {
                GC_Table[geno_sum][i] = temp;
                GC_Table[geno_sum][i]->next = NULL;
            }
            else
            {
                RSID* temp2 = GC_Table[geno_sum][i];
                if (temp2->id.compare(temp->id)>0)// if A>B A(B) you will get value greater that zero. B is what you want to insert
                {
                    temp->next = temp2;
                    GC_Table[geno_sum][i] = temp;
                    return;
                }
                while (temp2->next != NULL)
                {

                    if (temp2->next->id.compare(temp->id)>0)// if A<B A(B) alue less than 0
                    {
                       break;
                    }
                    temp2=temp2->next;

                }
                temp->next=temp2->next;
                temp2->next=temp;

            }

        }
    }
}*/
