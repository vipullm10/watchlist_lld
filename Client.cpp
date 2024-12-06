#include "datatypes.h";
#include <iostream>
#include <unordered_map>



//This class represents the end user i.e. the client / the end customer
class Client{
    private :
        uint64_t userid;
        std::unordered_map<uint32_t,uint32_t> watchList;
        uint16_t wathcListItemCount;
        
    public :
        Client(uint32_t userid){
            this->userid = userid;
            wathcListItemCount = 0;
        }

        uint16_t getPageNumber(uint16_t itemIndex){
            if(itemIndex > 500)
                return 0; //returning 0 as we do not have a valid page number for an item index > 0

            if(itemIndex%50 == 0)
                return itemIndex / 50; //returning the index / 50 if index is divisible by 50 (eg 50/50 = 1 , so the page number is 1)

            return (itemIndex / 50) + 1; //returning (index/50) + 1 if index is not divisible by 50 (eg 451 / 50 = 9.02 which is not perfectly divisible by 50 , so 451/50 as an int will give us 9 , so we return 9 + 1 = 10 )
        }

        //just a mock function that will send the request to the client server to add this particular token in this user's watchlist , so that we can start receiving data for this token
        bool sendWatchListRequest(uint32_t token,REQ_TYPE requestType){
            watchListRequest req;
            req.requestType = requestType;
            req.token = token;
            req.userid = userid;

            //send this http request to the client server 
            return true;
        }

        //function to add the security represented by this token to our watchlist
        bool addToWatchlist(uint32_t token){    
            //first we check if the security represented by this token is already added in the watchlist
            if(watchList.find(token) != watchList.end()){
                return false;
            }

            //then we check if the watchlist contains more than 500 stocks (since one page can have 10 stocks)
            if(wathcListItemCount >= 500){
                return false; //we cannot add any more stocks in our watchlist
            }

            //we send a request to the client server so that we can receive the feed data for this security
            if(!sendWatchListRequest(token,ADD))
                return false; //request failed , so return false

            //request was sent and response was received successfully 
            //we can add this token in user's watchlist
            watchList[token] = ++wathcListItemCount;
            
            return true; 
        }

        //function to remove the security represented by this token from our watchlist
        bool removeFromWatchList(uint32_t token){

            //first we check if the security represented by this token is added in the watchlist (just a safety check!)
            if(watchList.find(token) == watchList.end()){
                return false; //cannot remove as it was never added
            }
            
            //we send a request to the client server so that we can stop receiving the feed data for this security
            if(!sendWatchListRequest(token,REMOVE))
                return false; //request failed , so return false

            //request was sent , and response was received successfully
            //we can remove this token from the user's watchlist
            watchList.erase(token);

            //decrement watchlist item count so that more items can be added to the watchlist
            --wathcListItemCount;
            return true;
        }

        //function to process incoming data from the client server (this would be a callback function that would be called everytime data is received from the client server)
        void processReceivedFeed(watchListData item){
            
            //get page number of this particular token in our watchlist
            uint16_t pageNum = getPageNumber(item.data.token);
            if(!pageNum){
                //we got 0 as the page number , which means something went wrong. we can add this event in a log file and return from here
                return;
            }

            //we have a valid page number , now we can use this page number index to update the UI with the latest data received 
            switch (item.exchangetype)
            {
            case NSEEQ:
                /* code to update the NSE watchlist user interface for this security*/
                break;

            case BSEEQ:
                /* ccode to update the BSE watchlist user interface for this security */
                break;

            default:
                /* something went wrong (we received an invalid exchange type)*/
                break;
            }
        }


};