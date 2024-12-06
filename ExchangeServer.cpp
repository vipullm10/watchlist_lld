#include "datatypes.h"
#include <iostream>
#include <vector>


//This class respresents the end exchange (NSE/BSE) server
class ExchangeServer{
    private:
        std::vector<std::pair<uint64_t,uint64_t>> connections;
    public:
        ExchangeServer(){
            //can contain initialisation logic for this server
            //things like creating a server that listens to requests at a particular port
        }
        
        bool receiveConnection(uint64_t connectionId,uint64_t fd){
            //add this particular connection fd in our vector
            connections.push_back(std::pair<uint64_t,uint64_t>(connectionId,fd));
            return true;
        }

        bool removeConnection(uint64_t connectionId){
            //remove this particular connection id since it was disconnected 
            bool found = false;
            size_t index = 0;
            for(size_t i = 0;i<connections.size();i++){
                if(connections[i].first == connectionId){
                    index = i;
                    found = true;
                    break;
                }
            }
            if(!found){
                return false; //connection id not found so return false (SAFETY CHECK)
            }
            connections.erase(connections.begin()+index);
            return true;
        }


        //callback function which will be called everytime the exchange has to send data
        //this function will send data to a respective stream . (due to a shortage of time couln't exactly show the exact bifuraction at a stream level)
        void sendFeed(feedData data){
            for(std::pair<uint64_t,uint64_t> connectionId : connections){
                //we iterate over all connections and send them this payload
            }
        }
};