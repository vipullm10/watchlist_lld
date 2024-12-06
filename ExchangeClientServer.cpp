#include "datatypes.h"
#include <iostream>



//This class represents the server which is responsible for connecting with the exchange server
class ExchangeClientServer{
    private :
        uint16_t streamId;
        EXCHANGE_TYPE exchangeType;
    public :
        ExchangeClientServer(uint16_t streamId,EXCHANGE_TYPE exchangeType){
            this->streamId = streamId;
            this->exchangeType = exchangeType;
            //after setting these two variables , we will call the function that will start listening to data for that particular strem from that particular exchange
            //we can keep stream id and exchange type in a kind of a config file which will contain these two values as well as the connection paramters for the exchange servers for this particular stream
            //we will also do the initialisation part for the publisher which will help us publish the incoming payload from the exchange
        }


        //callback function that will be called everyime we receive tick data from the exchange
        void publishFeed(feedData data){
            watchListData dataToBePublished;
            memcpy(&dataToBePublished.data,&data,sizeof(feedData)); //copying feedData structure into our response structure which we publissh to the message broking service
            dataToBePublished.exchangetype = this->exchangeType; //setting the exchange type for this payload
            //then we can call a function which publish this payload to the message broking service
        }


};