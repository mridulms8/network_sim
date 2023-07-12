#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <bits/stdc++.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
using namespace std;
class Sender
{
    string Sdata;

public:
    Sender(string x)
    {
        Sdata = x;
    }
    void printData()
    {
        cout << "Data Sent: ";
        cout << Sdata << endl;
    }
};
class Receiver
{
    string Rdata;

public:
    Receiver(string x)
    {
        Rdata = x;
    }
    void printData()
    {
        cout << "Data Received: ";
        cout << Rdata << endl;
    }
};

////////////////// GLOBAL VARIABLES //////////////////

int oct2 = 0;    // Last octet
int oct1 = 0;    // 2nd Last
int iplast1 = 2; // Last portion of ips of network1
int iplast2 = 2; // Last porition of ips of network2

////////////////////////////////////////////////////////
//------- MAC ADDRESSES STROED BY THE SWITCH --------//
///////////////////////////////////////////////////////
void printIP(set<pair<int, string>> ip, unordered_map<int, vector<string>> &mac)
{
    cout << "\n-------------------------------------------------\n";
    cout << "|MAC\t\t\t|"
         << "Name\t\t\t|\n";
    cout << "-------------------------------------------------\n";
    for (auto x : ip)
    {
        cout << "|" << mac[x.first][0] << "\t|";
        if (x.second == "Charlie" || x.second == "Foxtrot")
            cout << x.second << "\t\t|\n";
        else
            cout << x.second << "\t\t\t|\n";
    }
    cout << "-------------------------------------------------\n";
}

//--- NOT IN USE NOT IN USE NOT IN USE NOT IN USE ---//
//--- NOT IN USE NOT IN USE NOT IN USE NOT IN USE ---//
//--- NOT IN USE NOT IN USE NOT IN USE NOT IN USE ---//
void printMac(set<pair<int, string>> ip)
{
    cout << "\n-------------------------------------------------\n";
    cout << "|Mac\t\t\t|\n";
    cout << "-------------------------------------------------\n";
    for (auto x : ip)
    {
        if (x.second == "Charlie" || x.second == "Foxtrot")
            cout << "|" << x.second << "\t\t|\n";
        else
            cout << "|" << x.second << "\t\t\t|\n";
    }
    cout << "-------------------------------------------------\n";
}

////////////////// BUILD EDGES OF GRAPH FUNCTION ///////////////////////

void makeEdge(vector<pair<int, string>> adj[], int i, int j, string data)
{
    adj[i].push_back({j, data});
}

//////////////////////////////////////////
//--------- ERROR GENERATION -----------//
//////////////////////////////////////////
string probability(string y, int &err)
{
    int randNo = rand() % 4;
    if (randNo == 0 || randNo == 1)
    {
        err = 0;
        return y;
    }
    else if (randNo == 2)
    {
        for (int i = 0; i < y.size(); ++i)
            y[i] = '0';
    }
    else
    {
        if (y.size() <= 2)
            for (char x : y)
                y = '0';
        else
        {
            if (y[0] == '1')
                y[0] = '0';
            else if (y[0] == '0')
                y[0] = '1';
            if (y[2] == '0')
                y[2] = '1';
            else if (y[2] == '1')
                y[2] = '0';
        }
    }
    err = 1;
    return y;
}
void printAdjList(vector<pair<int, string>> adj[], int n)
{
    for (int i = 0; i < n + 1; ++i)
    {
        cout << i << ": ";
        for (auto x : adj[i])
            cout << x.first << " ";
        cout << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------- INFORMATION ABOUT THE SENDERS AND RECIEVERS -----------------------------//
////////////////////////////////////////////////////////////////////////////////////////////////////////
void printInfoList(vector<pair<int, string>> adj[], int n, vector<string> name, vector<int> err, vector<int> sen, vector<int> rec, unordered_map<int, vector<string>> &mac)
{
    for (int i = -1; i <= n; ++i)
    {
        if (i == -1)
        {
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------\n";
            cout << "|Name\t\t|"
                 << "MAC Address\t\t|"
                 << "Sender\t\t|"
                 << "Receiver\t|"
                 << "Data Sent\t\t|"
                 << "Data Received\t\t|"
                 << "Error\t\t|\n";
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------\n";
        }
        else
        {
            if (name[i] == "Charlie" || name[i] == "Foxtrot")
            {
                cout << "|" << name[i] << "(" << i << ")"
                     << "\t|";
            }
            else
                cout << "|" << name[i] << "(" << i << ")"
                     << "\t|";
            cout << mac[i][0] << "\t|";
            cout << sen[i] << "\t\t|"
                 << rec[i] << "\t\t|";
            if (sen[i] == 1)
            {
                if (!i)
                    cout << adj[0][i].second << "\t\t\t|";
                else
                    cout << adj[i][0].second << "\t\t\t|";
            }
            else if (sen[i] != 1)
            {
                cout
                    << "---"
                    << "\t\t\t|";
            }
            if (rec[i] == 1)
            {
                if (!i)
                    cout << adj[0][i].second << "\t\t\t|";
                else
                    cout << adj[i][0].second << "\t\t\t|";
            }
            else if (rec[i] != 1)
            {
                cout
                    << "---"
                    << "\t\t\t|";
            }
            cout << err[i] << "\t\t|\n";
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------\n";
        }
    }
}

bool checksum()
{
    return true;
}

////////////////////////////////////////////////////////////////////////
///////////////////////////// + OUT //////////////////////////////////
/////////////////////////////////////////////////////////////////////////
bool timeOut()
{
    int t = rand() % 10;
    if (t % 3)
        return false;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////
//------------------------------- STOP AND WAIT ARQ ---------------------------------//
///////////////////////////////////////////////////////////////////////////////////////
void stopAndWaitARQ(int i, int sender, vector<pair<int, string>> adj[], vector<string> name)
{
    int j = 0;
    string s = adj[sender][0].second;
    while (j < s.size())
    {
        cout << "Sender " << name[sender] << "(" << sender << ")"
             << " is now sending " << s[j] << " and waiting for ack" << endl;
        if (checksum() && adj[i][0].second[j] != s[j])
        {
            cout << "Receiver " << name[i] << "(" << i << ")"
                 << " received " << adj[i][0].second[j] << endl;
            cout << name[i] << "(" << i << ")"
                 << " asks to send the frame again" << endl;
            cout << name[sender] << "(" << sender << ")"
                 << " receives ack "
                 << " and send " << s[j] << " again." << endl;
            adj[i][0].second[j] = s[j];
            cout << name[i] << "(" << i << ")"
                 << " receives " << s[j] << " and sends the ack to sender" << endl;
        }
        else
        {
            cout << name[i] << "(" << i << ")"
                 << " receives " << s[j] << " and sends the ack to sender" << endl;
            while (timeOut())
            {
                cout << "******TIME OUT!!!"
                     << " Ack not received.******" << endl;
                cout << "Sender " << name[sender] << "(" << sender << ")"
                     << " is now sending " << s[j] << " and waiting for ack" << endl;
                cout << name[i] << "(" << i << ")"
                     << " receives " << s[j] << " and sends the ack to sender" << endl;
            }
        }
        cout << endl;
        j++;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//------------------------------ SELECTIVE REPEAT ARQ ------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////
void selectiveRepeatARQ(int i, int sender, vector<pair<int, string>> adj[], vector<string> name)
{
    int j = 0;
    int window;
    string s = adj[sender][0].second;
    if (s.size() % 2 == 0)
        window = 2;
    else
    {
        window = 1;
    }
    cout << "\nWindow size used in Selective Repeat ARQ is : " << window << endl
         << endl;
    if (window == 2)
    {
        while (j < s.size())
        {
            cout << "Sender " << name[sender] << "(" << sender << ")"
                 << " is now sending " << s[j] << s[j + 1] << " and waiting for ack" << endl;
            string s1, r1;
            s1.push_back(s[j]);
            s1.push_back(s[j + 1]);
            r1.push_back(adj[i][0].second[j]);
            r1.push_back(adj[i][0].second[j + 1]);
            if (checksum() && r1 != s1)
            {
                cout << "Receiver " << name[i] << "(" << i << ")"
                     << " received " << r1 << endl;
                cout << name[i] << "(" << i << ")"
                     << " asks to send the frame again" << endl;
                cout << name[sender] << "(" << sender << ")"
                     << " receives ack "
                     << " and send " << s1 << " again." << endl;

                adj[i][0].second[j] = s1[0];
                adj[i][0].second[j + 1] = s1[1];
                cout << name[i] << "(" << i << ")"
                     << " receives " << s1 << " and sends the ack to sender" << endl;
            }
            else
            {
                cout << name[i] << "(" << i << ")"
                     << " receives " << s1 << " and sends the ack to sender" << endl;
                while (timeOut())
                {
                    cout << "****TIME OUT!!!"
                         << " Ack not received.****" << endl;
                    cout << "Sender " << name[sender] << "(" << sender << ")"
                         << " is now sending " << s[j] << s[j + 1] << " and waiting for ack" << endl;
                    cout << name[i] << "(" << i << ")"
                         << " receives " << s1 << " and sends the ack to sender" << endl;
                }
            }
            cout << endl;
            j += 2;
        }
    }
    else
    {
        while (j < s.size())
        {
            cout << "Sender " << name[sender] << "(" << sender << ")"
                 << " is now sending " << s[j] << " and waiting for ack" << endl;
            if (adj[i][0].second[j] != s[j])
            {
                cout << "Receiver " << name[i] << "(" << i << ")"
                     << " received " << adj[i][0].second[j] << endl;
                cout << name[i] << "(" << i << ")"
                     << " asks to send the bit again" << endl;
                cout << name[sender] << "(" << sender << ")"
                     << " receives ack "
                     << " and send " << s[j] << " again." << endl;
                adj[i][0].second[j] = s[j];
                cout << name[i] << "(" << i << ")"
                     << " receives " << s[j] << " and sends the ack to sender" << endl;
            }
            else
            {
                cout << name[i] << "(" << i << ")"
                     << " receives " << s[j] << " and sends the ack to sender" << endl;
                while (timeOut())
                {
                    cout << "*****TIME OUT!!!"
                         << " Ack not received*****." << endl;
                    cout << "Sender " << name[sender] << "(" << sender << ")"
                         << " is now sending " << s[j] << " and waiting for ack" << endl;
                    cout << name[i] << "(" << i << ")"
                         << " receives " << s[j] << " and sends the ack to sender" << endl;
                }
            }
            cout << endl;
            j++;
        }
    }
}

////////////////////////////// GENERATION OF MAC //////////////////////////////////

void generateMAC1(unordered_map<int, vector<string>> &mac, vector<string> &name, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        string oct = "00-AA-BB-CC-DD-0";
        oct += '0' + oct2++;
        mac[i] = {oct};
    }
}

void generateMAC2(unordered_map<int, vector<string>> &mac, int i, int n)
{
    for (; i <= n; ++i)
    {
        string octet = "00-AA-BB-CC-DD-";
        octet += '0' + oct2++;
        string oct = octet + "0";
        mac[i] = {oct};
    }
}

//////////////////////////// GENERATION OF IP /////////////////////////////////////

void generateIP1(unordered_map<int, vector<string>> &ipAdd, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        ipAdd[i] = {"10.0.0." + to_string(iplast1++) + "/24"};
    }
}

void generateIP2(unordered_map<int, vector<string>> &ipAdd, int i, int n)
{
    for (; i <= n; ++i)
    {
        ipAdd[i] = {"20.0.0." + to_string(iplast2++) + "/24"};
    }
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// REMOVAL OF THE DATA ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void RemovalOfData(vector<pair<int, string>> adj[], vector<string> &name, int n)
{
    for (int i = 0; i <= n + 1; ++i)
    {
        for (int j = 0; j < adj[i].size(); ++j)
        {
            adj[i][j].second = "";
        }
    }
}

/////////////////////// PRINTING OF THE PATHS ////////////////////////////////////
void printPath(vector<vector<int>> rout[], vector<vector<int>> &dist)
{
    int len = 3;
    while (len--)
    {
        cout << "|Source Router\t|Next Router\t|Distance\t|\n";
        cout << "---------------------------------------\n";
        for (int i = 0; i < 3; ++i)
        {
            cout << "|" << 3 - len << "\t\t|" << i + 1 << "\t\t|" << dist[2 - len][i];
            cout << "---------------------------------------\n";
        }
        cout << "\n\n";
    }
}
///////////////////////////// DNS ///////////////////////////////////////////

void dns(string s)
{
    std::string domainName = s; // Replace with your desired domain name

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(domainName.c_str(), NULL, &hints, &res);
    if (status != 0)
    {
        std::cerr << "Failed to get address info: " << gai_strerror(status) << std::endl;
        return;
    }

    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    char ipAddress[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(ipv4->sin_addr), ipAddress, INET_ADDRSTRLEN);

    std::cout << "IP Address for " << domainName << " is: " << ipAddress << std::endl;

    freeaddrinfo(res);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DRIVER FUNCTION /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int main()
{
    int h = 0;
    char res = 'x';
    while (res != 'Y' && res != 'y' && res != 'N' && res != 'n')
    {
        cout << "Do You Want hub in the network: (y/n)\n";
        cin >> res;
    }
    if (res == 'Y' || res == 'y')
    {
        int hub;
        cout << "How many hubs do you want in the network?(<=2) :\n";
        cin >> hub;
        string data;
        int n;
        cout << "How many devices do you want to be connected to the hub (At least two and at most 10) : ";
        cin >> n;
        srand(time(0));
        vector<pair<int, string>> adj[50];
        vector<string> name = {"Hub1", "Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "India", "Juliet", "King", "Hub2"};
        cout << "\nThe name of the devices are as follows :\n\n";

        ///////////////////// MAC ADDRESS ALLOCATION ///////////////////////////////////

        unordered_map<int, vector<string>> mac; // Vector of Strings in case of multiple macs of a router
        generateMAC1(mac, name, n);
        mac[0] = {"-----------------"};

        for (int i = 1; i <= n; ++i)
            if (i != 11)
                cout << name[i] << "(" << i << ") ";
        cout << "\n\n";
        int sender = rand() % n + 1;
        if (sender == 11)
            sender = 10;
        int recSize = n - rand() % n + 1;
        if (recSize > n - 3)
        {
            recSize = n - 3;
        }
        cout << "No. of receivers : " << recSize << endl
             << endl;
        // cout << name[sender] << "(" << sender << ") "
        //      << "has been set as the sender\n\n";
        cout << "Enter the data to be sent in bits: ";
        cin >> data;
        vector<int> sen(n + 1, 0), rec(n + 1, 1), rec1(n + 1, 0), rec2(n + 1, 0);
        vector<int> err(n + 1, 0);
        // Sender S(data);
        if (hub == 2 && sender > 5)
        {
            makeEdge(adj, sender, 11, data);
            makeEdge(adj, 11, sender, data);
        }
        else
        {
            makeEdge(adj, sender, h, data); // Data Send to the Hub
            makeEdge(adj, h, sender, data); // Hub Receives the data
        }
        // vector<int> sen(n + 1, 0), rec(n + 1, 1), rec1(n + 1, 0), rec2(n + 1, 0);
        sen[sender] = 1;
        sen[h] = 1;
        rec[sender] = 0;
        char token = 'x';
        while (token != 'y' && token != 'Y' && token != 'n' && token != 'N')
        {
            cout << "Do you want to use Token passing (y/n)?\n";
            cin >> token;
        }
        int lenOfRec = recSize;
        if (token == 'y' || token == 'Y')
        {
            cout << "'" << name[sender] << "'"
                 << " is sending the data." << endl;
            for (int i = 1; i < n + 1; ++i)
            {
                if (i != sender && lenOfRec)
                {
                    cout << "Now, "
                         << "'" << name[i] << "'"
                         << " has the access of the channel." << endl;
                    lenOfRec--;
                    if (lenOfRec)
                        cout << "Token is being passed to the successor." << endl;
                }
            }
        }
        else
        {
            cout << name[sender] << "(" << sender << ") "
                 << "has been set as the sender\n\n";
        }
        if (hub == 2) //////////////////////////////////////////////  MULTIPLE HUBS CASE
        {
            rec.push_back(1);
            err.push_back(0);
            sen.push_back(1);
            makeEdge(adj, 11, 0, data);
            makeEdge(adj, 0, 11, data);
            sen[sender] = 1;
            sen[0] = 1;
            rec[sender] = 0;
            int firsthalf = -1;
            // rec = {1}, err = {0}
            for (int i = 1; i <= 5; ++i)
            {
                if (sen[i] == 1)
                {
                    firsthalf = 1;
                    break;
                }
            }
            // if(firsthalf == 1)
            for (int i = 1; i <= 5; ++i)
            {
                if (i != sender)
                {
                    makeEdge(adj, i, 0, data);
                    makeEdge(adj, 0, i, data);
                }
            }
            for (int j = 6; j <= 10; ++j)
            {
                if (j != sender)
                {
                    makeEdge(adj, j, 11, data);
                    makeEdge(adj, 11, j, data);
                }
            }
            printInfoList(adj, 11, name, err, sen, rec, mac);
            printAdjList(adj, 11);
            cout << "\nNumber of broadcast domains : " << hub << endl;
            cout << "\nNumber of collision domains : " << adj[0].size() + adj[11].size() << endl;
            return 1;
        }
        // vector<int> err(n + 1, 0);
        err[0] = 0;
        for (int i = 1; i <= n + 1; ++i)
        {
            if (i != sender)
            {
                string s = data;
                int x = 0;
                s = probability(s, x);
                err[i] = x;
                makeEdge(adj, h, i, data); // Hub Sends the data
                makeEdge(adj, i, h, s);    // Receiver receives the data
            }
        }
        rec1 = rec;
        char access = 'x';
        while (access != 'Y' && access != 'y' && access != 'N' && access != 'n')
        {
            cout << "Do you want to use Access Control Protocols?(y/n)\n";
            cin >> access;
        }
        int protocol = 0;
        if (access == 'Y' || access == 'y')
        {
            while (protocol != 1 && protocol != 2)
            {
                cout << "Which protocol do you want to use?\n1.Stop and Wait ARQ\n2.Selective Repeat ARQ\n0.Don't use\n";
                cin >> protocol;
                if (protocol == 0)
                    break;
            }
        }
        int swit = recSize; // swit is the count of number of receivers
        cout << "\nResults after broadcasting by the hub: \n";
        // cout << "Select the methods using which you want to see the information of the data devices sent/received: \n";
        // cout << "1. Graph\n2. Classes\n";
        printInfoList(adj, n, name, err, sen, rec, mac);
        vector<int> err1 = err;
        int j = 0;
        while (recSize && j < n + 1)
        {
            if (j != sender && j != 0)
            {
                rec[j] = 1;
                recSize--;
            }
            j++;
        }
        while (j < n + 1)
        {
            rec[j] = 0;
            err[j] = 0;
            j++;
        }
        rec2 = rec;
        cout << "\nBut the data was to be received by: \n";
        for (int i = 0; i < n + 1; ++i)
            if (rec[i] == 1)
                cout << name[i] << " ";
        cout << endl
             << endl;
        cout << "\nResults after passing through a bridge: \n";
        printInfoList(adj, n, name, err, sen, rec, mac);
        cout << "\nNow showing the same data using a switch: \n";
        j = 1;
        int cnt = 2;
        cout << "\nResults after pass 1: \n";
        printInfoList(adj, n, name, err, sen, rec1, mac);
        set<int> set1;
        while (j < n + 1 && cnt <= swit + 1)
        {
            err = err1;
            for (int x : rec)
                x = 1;
            if (j == sender)
                j = j + 1;
            set1.insert(j);
            rec = rec1;
            for (int i = 1; i < n + 1; ++i)
            {
                if (i != j)
                {
                    rec[i] = 0;
                    err[i] = 0;
                }
            }
            printInfoList(adj, n, name, err, sen, rec, mac);
            rec = rec1;
            // for (int i = 1; i < n + 1; ++i)
            // {
            //     if (set1.find(i) != set1.end())
            //     {
            //         rec[i] = 0;
            //         err[i] = 0;
            //     }
            // }
            rec[sender] = 0;
            err[sender] = 0;
            cout << "\nResults after " << cnt << " pass :\n";
            vector<int> ip(n + 1, 0);
            printInfoList(adj, n, name, err1, sen, rec, mac);
            cnt++;
            j++;
        }
        set<pair<int, string>> ip;
        for (int i = 0; i < n + 1; ++i)
        {
            if (rec2[i] == 1)
                ip.insert({i, name[i]});
        }
        printIP(ip, mac); /// MAC ADDRESS PRINTED NOT IP!!!!
        cout << "\nResults after successful reception of data: \n";
        printInfoList(adj, n, name, err1, sen, rec2, mac);
        cout << "So, ";
        for (int i = 0; i < n + 1; ++i)
        {
            if (rec2[i] == 0 && i != sender)
                cout << name[i] << " ";
        }
        int countError = 0;
        for (int i = 0; i < n + 1; ++i)
        {
            if (err1[i] == 1 && rec2[i] == 1)
                countError++;
        }
        cout << "dropped the packets\n";
        if (protocol == 1)
        {
            cout << "\n\nNow using Stop and Wait ARQ to correct error in message recevied : \n";
            if (countError == 0)
            {
                cout << "No error message received." << endl;
                return 1;
            }
            for (int i = 1; i < n + 1; ++i)
            {
                if (rec2[i] == 1)
                    stopAndWaitARQ(i, sender, adj, name);
                cout << endl;
            }
            vector<int> errSWA(n + 1, 0);
            cout << "\nAfter Error Correction, final data received: \n";
            printInfoList(adj, n, name, errSWA, sen, rec2, mac);
        }
        else if (protocol == 2)
        {
            cout << "\n\nNow using Selective Repeat ARQ to : \n";
            if (countError == 0)
            {
                cout << "No error message received." << endl;
            }
            else
            {
                for (int i = 1; i < n + 1; ++i)
                {
                    if (rec2[i] == 1)
                        selectiveRepeatARQ(i, sender, adj, name);
                    cout << endl;
                }
                vector<int> errSWA(n + 1, 0);
                cout << "\nAfter Error Correction, final data received: \n";
                printInfoList(adj, n, name, errSWA, sen, rec2, mac);
            }
        }

        ////// REMOVE THE DATA FROM EACH RECEIVER AND MOVE FORWARD TO THE N/W LAYER //////

        vector<string> tempName = name;
        name = vector<string>(n + 1);

        for (int i = 0; i <= n; ++i)
        {
            name[i] = tempName[i];
        }

        RemovalOfData(adj, name, n);
        rec = vector<int>(n + 1), sen = rec;
        printInfoList(adj, n, name, err, sen, rec, mac);

        ////////// NETWORK LAYER BEGINS HERE //////////////////////////////////////////

        vector<string> name2 = {"Hub3", "Omen", "Legion", "Alienware", "ROG", "Pavillion", "IdeaPad", "Air", "Pro", "G15", "TUF", "Hub4"};
        vector<pair<int, string>> adj2[50];
        int n2 = 13;
        while (n2 > 12)
        {
            cout << "How many devices do you need in network 2? : ";
            cin >> n2;
        }

        ////////////////////// ADDING ROUTER IN NETWORK 1 //////////////////////////////////////////////////////////////////////////////

        int r1 = n + 1;
        name.push_back("r1-2621XM");
        for (int i = 1; i <= n; i++)
        {
            makeEdge(adj2, r1, i, "");
            makeEdge(adj2, i, r1, "");
        }
        unordered_map<int, vector<string>> ipAdd;
        ipAdd[0] = {"--------------"};
        generateIP1(ipAdd, n);

        ////// ASSIGNING MAC & IP ADDRESSES TO THE ROUTER 1 ////////
        string s1 = "00-AA-BB-CC-DD-0", s2 = "00-AA-BB-CC-DD-0", s3 = "00-AA-BB-CC-DD-0", s4 = "00-AA-BB-CC-DD-0"; // 3 INTERFACES AT MAX
        s1 += '0' + oct2++, s2 += '0' + oct2++, s3 += '0' + oct2++, s4 += '0' + oct2++;
        mac[r1] = {s1, s2, s3};
        ipAdd[r1] = {"10.0.0.1/24", "30.0.0.2/23", "50.0.0.1/23"};

        ////////////////////// ADDING NETWORK 2 TO NETWORK 1 //////////////////////////////////////////////////////////////////////////////
        int h2 = n + 2; /// Hub of the second network if required
        name.push_back("Hub3");
        ////// Partially connecting both the networks ////
        for (int i = 1; i <= n2; ++i)
        {
            name.push_back(name2[i]);
        }
        ////////////////////// ADDING ROUTER IN NETWORK 2 //////////////////////////////////////////////////////////////////////////////
        int r2 = name.size();
        name.push_back("r2-2621XM");
        for (int i = h2 + 1; i <= r2 - 1; ++i)
        {
            makeEdge(adj2, r2, i, "");
            makeEdge(adj2, i, r2, "");
        }
        ipAdd[h2] = {"--------------"};
        ipAdd[r2] = {"20.0.0.1/24", "40.0.0.2/23", "50.0.0.2/23"};
        mac[r2] = {"00-DD-BB-CC-DD-EE", "00-DD-BB-CC-DD-EE", "00-DD-BB-CC-DD-EF"};
        generateMAC2(mac, h2 + 1, r2 - 1);
        generateIP2(ipAdd, h2 + 1, r2 - 1);

        //// Connecting r1 with r2 /////
        makeEdge(adj2, r1, r2, "");
        makeEdge(adj2, r2, r1, "");
        ///////////////////////////////

        /////////////////// ADDING ROUTER 3 //////////////////////////////////////////////////////////////////////////////////
        int r3 = name.size();
        name.push_back("r3-2621XM");
        ipAdd[r3] = {"30.0.0.1/23", "40.0.0.1/23"};
        mac[r3] = {"00-DD-BB-CC-DD-CE", "00-DD-BB-CC-DD-CD"};
        ////  Connecting the routers ////
        makeEdge(adj2, r1, r3, "");
        makeEdge(adj2, r3, r1, "");
        makeEdge(adj2, r2, r3, "");
        makeEdge(adj2, r3, r2, "");
        ///////////////////////////////

        //// DATA TRANSFER ////
        int sid, rid;
        cout << "Choose the device from which you want to transfer the data: \n";
        for (int i = 1; i < r3; ++i)
        {
            if (i != r1 && i != r2 && i != h2)
                cout << i << ". " << ipAdd[i][0] << endl;
        }
        cin >> sid;
        cout << "Choose the device to which you want to send the data: \n";
        int a, b;
        if (sid > 0 && sid < r1)
            a = h2 + 1, b = r2;
        if (sid > r2)
            a = 1, b = r1;
        for (int i = a; i < b; ++i)
        {
            if (i != r1 && i != r2 && i != h2 && i != sid)
                cout << i << ". " << ipAdd[i][0] << endl;
        }
        cin >> rid;
        string dt;
        cout << "Enter the data to send: ";
        cin >> dt;
        string domain;
        cout << "enter the domainName: ";
        cin >> domain;

        vector<string> hostAdd1 = {"10.0.0.0/24", "30.0.0.0/23", "50.0.0.0/23"};
        vector<string> hostAdd2 = {"20.0.0.0/24", "40.0.0.0/23", "50.0.0.0/23"};
        vector<string> hostAdd3 = {"30.0.0.0/24", "40.0.0.0/23"};
        cout << "Source IP Address: " << ipAdd[sid][0] << "\n";
        cout << "Destination IP Address: " << ipAdd[rid][0] << endl
             << endl
             << endl;

        int route = 3;
        while (route != 1 && route != 2)
        {
            cout << "\n\n\nChoose the type of Routing: " << endl;
            cout << "1. Static Routing" << endl;
            cout << "2. Dynamic Routing" << endl;
            cin >> route;
        }
        if (route == 1)
        {
            if (sid > 0 && sid < r1)
            {
                cout << "Routing Table for " << name[r1] << " : \n";
                cout << "-----------------------------------------\n";
                cout << "|Interface No.\t|"
                     << "Host Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 1 << "\t\t|" << hostAdd1[0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 2 << "\t\t|" << hostAdd1[1] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 3 << "\t\t|" << hostAdd1[2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "Routing Table for " << name[r2] << " : \n";
                cout << "-----------------------------------------\n";
                cout << "|Interface No.\t|"
                     << "Host Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 4 << "\t\t|" << hostAdd2[0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 5 << "\t\t|" << hostAdd2[1] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 6 << "\t\t|" << hostAdd2[2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "Routing Table for " << name[r3] << " : \n";
                cout << "-----------------------------------------\n";
                cout << "|Interface No.\t|"
                     << "Host Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 7 << "\t\t|" << hostAdd3[0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 8 << "\t\t|" << hostAdd3[1] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "Since the IP address of the destination belongs to a foreign network\n";
                cout << "so the data packet has to travel through the default gateway.\n";
                cout << "Source sends an ARP request to the switch to get the MAC of DG.\n";

                cout << "\n\nMAC Table for Switch 1 when the request is sent: \n\n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << sid << "\t\t|" << mac[sid][0] << "\t|\n";
                cout << "-----------------------------------------\n";

                cout << "Switch then broadcasts.....\n";

                cout << "\n\nMAC Table for Switch 1 after the response from the router1: \n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << sid << "\t\t|" << mac[sid][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r1 << "\t\t|" << mac[r1][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the router after generating ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of Source\t|"
                     << "MAC of source\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[sid][0] << "\t|" << mac[sid][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the sender after receiving the ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of router\t|"
                     << "MAC of router\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r1][0] << "\t|" << mac[r1][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "Now, router1 sends the ARP request to the Switch 2\n\n";
                cout << "";
                cout << "\n\nMAC Table for Switch 2 when the request is sent: \n\n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r1 + 1 << "\t\t|" << mac[r1][1] << "\t|\n";
                cout << "-----------------------------------------\n";

                cout << "Switch then broadcasts.....\n";

                cout << "\n\nMAC Table for Switch 2 after the response from the router1: \n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r1 + 1 << "\t\t|" << mac[r1][1] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r2 + 1 << "\t\t|" << mac[r1][1] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the router2 after generating ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of Source\t|"
                     << "MAC of source\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r1][2] << "\t|" << mac[r1][2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the router1 after receiving the ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of receiver\t|"
                     << "MAC of receiver\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r2][2] << "\t|" << mac[r2][2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "Now, router2 sends the ARP request to the Switch 3\n\n";
                cout << "";
                cout << "\n\nMAC Table for Switch 3 when the request is sent: \n\n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r2 << "\t\t|" << mac[r2][0] << "\t|\n";
                cout << "-----------------------------------------\n";

                cout << "Switch then broadcasts.....\n";

                cout << "\n\nMAC Table for Switch 2 after the response from the router2: \n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r2 << "\t\t|" << mac[r2][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << rid << "\t\t|" << mac[rid][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the destination after generating ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of Source\t|"
                     << "MAC of source\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r2][0] << "\t|" << mac[r2][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the router2 after receiving the ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of receiver\t|"
                     << "MAC of receiver\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r1][2] << "\t|" << mac[r1][2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[rid][0] << "\t|" << mac[rid][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "The Message: " << dt << " has been received successfully." << endl
                     << endl;
            }
        }
        else
        {
            cout << "\nOSPF routing protocol is being used here.\n\n";
            vector<vector<int>> rout[20];
            int r11 = 0, r21 = 1, r31 = 2;
            int d12 = 6, d13 = 5, d32 = 7;
            rout[r11].push_back({r21, d12});
            rout[r21].push_back({r11, d12});
            rout[r11].push_back({r31, d13});
            rout[r31].push_back({r11, d13});
            rout[r31].push_back({r21, d32});
            rout[r21].push_back({r31, d32});
            vector<vector<int>> dist(3);
            int src = 0;
            for (int i = 0; i < 3; ++i)
            {
                set<vector<int>> st;
                vector<int> d(3, INT_MAX);
                d[src] = 0;
                st.insert({d[src], src});
                while (st.size())
                {
                    auto cur = *st.begin();
                    st.erase(cur);
                    for (auto x : rout[cur[1]])
                    {
                        if (d[x[0]] > d[cur[1]] + x[1])
                        {
                            if (d[x[0]] != INT_MAX)
                                st.erase({d[x[0]], x[0]});
                            d[x[0]] = d[cur[1]] + x[1];
                            st.insert({d[x[0]], x[0]});
                        }
                    }
                }
                dist[src] = {d};
                src++;
            }
            cout << "After Applying Dijkstra Algorithm\n";
            cout << "Shortest paths found: \n";
            printPath(rout, dist);
            if (sid > 0 && sid < r1)
            {
                cout << "Routing Table for " << name[r1] << " : \n";
                cout << "-----------------------------------------\n";
                cout << "|Interface No.\t|"
                     << "Host Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 1 << "\t\t|" << hostAdd1[0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 2 << "\t\t|" << hostAdd1[1] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 3 << "\t\t|" << hostAdd1[2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "Routing Table for " << name[r2] << " : \n";
                cout << "-----------------------------------------\n";
                cout << "|Interface No.\t|"
                     << "Host Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 4 << "\t\t|" << hostAdd2[0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 5 << "\t\t|" << hostAdd2[1] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << 6 << "\t\t|" << hostAdd2[2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "Since the IP address of the destination belongs to a foreign network\n";
                cout << "so the data packet has to travel through the default gateway.\n";
                cout << "Source sends an ARP request to the switch to get the MAC of DG.\n";

                cout << "\n\nMAC Table for Switch 1 when the request is sent: \n\n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << sid << "\t\t|" << mac[sid][0] << "\t|\n";
                cout << "-----------------------------------------\n";

                cout << "Switch then broadcasts.....\n";

                cout << "\n\nMAC Table for Switch 1 after the response from the router1: \n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << sid << "\t\t|" << mac[sid][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r1 << "\t\t|" << mac[r1][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the router after generating ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of Source\t|"
                     << "MAC of source\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[sid][0] << "\t|" << mac[sid][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the sender after receiving the ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of router\t|"
                     << "MAC of router\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r1][0] << "\t|" << mac[r1][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "Now, router1 sends the ARP request to the Switch 2\n\n";
                cout << "";
                cout << "\n\nMAC Table for Switch 2 when the request is sent: \n\n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r1 + 1 << "\t\t|" << mac[r1][1] << "\t|\n";
                cout << "-----------------------------------------\n";

                cout << "Switch then broadcasts.....\n";

                cout << "\n\nMAC Table for Switch 2 after the response from the router1: \n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r1 + 1 << "\t\t|" << mac[r1][1] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r2 + 1 << "\t\t|" << mac[r1][1] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the router2 after generating ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of Source\t|"
                     << "MAC of source\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r1][2] << "\t|" << mac[r1][2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the router1 after receiving the ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of receiver\t|"
                     << "MAC of receiver\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r2][2] << "\t|" << mac[r2][2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "Now, router2 sends the ARP request to the Switch 3\n\n";
                cout << "";
                cout << "\n\nMAC Table for Switch 3 when the request is sent: \n\n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r2 << "\t\t|" << mac[r2][0] << "\t|\n";
                cout << "-----------------------------------------\n";

                cout << "Switch then broadcasts.....\n";

                cout << "\n\nMAC Table for Switch 2 after the response from the router2: \n";
                cout << "-----------------------------------------\n";
                cout << "|Port No.\t|"
                     << "MAC Address\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << r2 << "\t\t|" << mac[r2][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << rid << "\t\t|" << mac[rid][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the destination after generating ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of Source\t|"
                     << "MAC of source\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r2][0] << "\t|" << mac[r2][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "ARP Table for the router2 after receiving the ARP response: \n";
                cout << "-----------------------------------------\n";
                cout << "|IP of receiver\t|"
                     << "MAC of receiver\t\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[r1][2] << "\t|" << mac[r1][2] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "|" << ipAdd[rid][0] << "\t|" << mac[rid][0] << "\t|\n";
                cout << "-----------------------------------------\n";
                cout << "\n\n";

                cout << "The Message: " << dt << " has been received successfully." << endl
                     << endl;
            }
        }
        cout << endl;
        dns(domain);
        // staticRouting();
        // printMacTable();
        // printMacTable();
        // printARPTable();
        // printARPTable();
        // printRoutingTable();
        // printRoutingTable();

        printAdjList(adj2, r3);
    }
    else
    {
        vector<pair<int, string>> adj[2];
        string x;
        cout << "Enter the data to be sent in bits: ";
        cin >> x;
        Sender s(x);
        makeEdge(adj, 0, 1, x);
        s.printData();
        int err = 0;
        x = probability(x, err);
        Receiver r(x);
        makeEdge(adj, 1, 0, x);
        r.printData();
        if (err)
            cout << "Data was received with error!" << endl;
        else
            cout << "Correct data was received." << endl;
    }
    return 0;
}