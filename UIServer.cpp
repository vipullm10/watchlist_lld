#include "datatypes.h"
#include <iostream>
#include <vector>
#include <unordered_map>




//This class represents the server with which the end customer will interact
class UIServer{
    private:
        std::unordered_map<uint32_t,std::vector<uint64_t>> tokenUserMapping; //map that will tell us this token is added in which all user's watchlist
    public:
        UIServer(){
            //logic to initialise ui server
            //contain parts like establishing connection with message broker service 
        }

        //function to process incoming requests from the clientss
        //just for simulation purposes , a true return value from this function would mean that the user request was successfully processed , a false return would indicate an error
        bool processClientRequest(watchListRequest request){
            switch (request.requestType)
            {
            case ADD:
                if(tokenUserMapping.find(request.token) == tokenUserMapping.end()){
                    //this means that this token has not yet been added by any user to their watchlist
                    //so we create a mapping for this token and add this user to the vector for this token
                    std::vector<uint64_t> users;
                    users.push_back(request.userid);
                    tokenUserMapping[request.token] = users;
                    return true;
                }
                else{
                    //this means that this token has already been added by someone in their watchlist since we find this token in our mapping
                    std::vector<uint64_t> &users = tokenUserMapping[request.token];
                    for(uint64_t userid : users){
                        if(userid == request.userid)
                            return false; //this means that this token has already been added by this user in their watchlist , so we don't add again(SAFETY CHECK)
                    }
                    //token not already added by user , so we can add this user 
                    users.push_back(request.userid);
                    tokenUserMapping[request.token] = users;
                    return true;
                }
            case REMOVE:
                if(tokenUserMapping.find(request.token) == tokenUserMapping.end()){
                    //this means that this token has not yet been added by any user to their watchlist
                    //so we cannot remove this token 
                    //(SAFETY CHECK)
                    return false;
                }
                else{
                    //this means that this token has already been added by someone in their watchlist since we find this token in our mapping
                    bool foundUser = false;
                    size_t index = 0;
                    std::vector<uint64_t> &users = tokenUserMapping[request.token];
                    for(size_t i = 0; i<users.size() ; i++){
                        if(users[i] == request.userid){
                            foundUser = true;
                            index = i;
                            break;
                        }
                    }
                    if(foundUser){
                        //remove this user from our vector
                        users.erase(users.begin()+index);
                        if(!users.size()){
                            //this means there are 0 users who have added this token to their watchlist , so we remove this token from our map
                            tokenUserMapping.erase(request.token);
                        }
                        tokenUserMapping[request.token] = users;
                        return true;
                    } 
                    //this means this token was not added by the user in their watchlist , so we return false (SAFETY CHECK)
                    return false;   
                }
            default:
                /* invalid request type received , we can log this event and return false*/
                break;
            }
            return false; //the only case this happens is in the case of default , else we return something from ADD/REMOVE cases and execution never reaches this line
        }

        //callback function which will process messages received from the message broking service
        void processReceivedFeed(watchListData item){
            
            //first we check if this security has been added by any user in their watchlists
            if(tokenUserMapping.find(item.data.token) == tokenUserMapping.end())
                return; //we simply ignore this data as this has not been added by any user in their watchlist

            //we retrieve the list of users who have added this security in their watchlists , and we send them this data received
            std::vector<uint64_t> &users = tokenUserMapping[item.data.token];
            for(uint64_t userid : users){
                //we can call the function to send a payload representing the requested data for this security to this user
            }
        }
};