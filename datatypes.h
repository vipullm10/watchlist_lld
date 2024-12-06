#include <stdint.h>


//exchange type , 1 represents NSEEQ and 2 represents BSEEQ
enum EXCHANGE_TYPE {NSEEQ = 1,BSEEQ = 2};


//request type , 1 represents addition to watchlist , 2 represents removal from watchlist
enum REQ_TYPE {ADD = 1,REMOVE = 2};

//structure for representing every security that is traded in the markets 
struct security
{
    uint32_t token; //unique integer identifier for every symbol (for eg RELIANCE can be represented by integer 1 , ADANI can be represented by integer 2 and so on)
    char symbol[20]; //full symbol name of the security (for eg. RELIANCE)
};


//structure used by the exchange servers to communicate feed data
struct feedData
{
    uint32_t token; //unique identifier
    uint32_t last_traded_price; //last price at which a trade occured for this particular security
};



//structure used by the UI servers to communicate data with clients 
struct watchListData
{
    feedData data; 
    EXCHANGE_TYPE exchangetype;
};



//structure of request from client to UI server  
struct watchListRequest
{
    uint32_t userid; //represents unique userid 
    uint32_t token; 
    REQ_TYPE requestType;
};