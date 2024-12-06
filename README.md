# watchlist_lld
![Watchlist_HLD](https://github.com/user-attachments/assets/b8044f7d-bd3e-4e43-9d17-da7fd85e716e)

There are 3 main components in the system . 
1) UI Server
2) Message Broking Service
3) Client Server

# Client Server
The client server is responsible to fetch data from the exchange . Since there can be a very large number of securities which can be traded on an exchange , we can divide the data transfer from the exchange to our own client server into separate streams . The way we can create streams is by dividing the streams based on the initial letter of the security . For eg . security symbols starting with the letters ('A' , 'B' , 'C' , 'D' , 'E') can go into stream id 1 , symbols starting with the letters ('F','G','H','I','J') will go in stream id 2 and so on and so forth . Every exchange server will have these different stream ids where they will be sending data . 

So , the client server component will listen for data of an individual stream from an exchange (NSE OR BSE) and then publish the received data to the message broking service . Every security will be represented by a fixed token number across exchanges so that we can easily process the received data identified by the token (this is an assumption we make! If this is not the case , then it can be handled at the client side) . 

# Message Broking Service
This can be any message broking service like kafka . We will publish data in the client server and listen for it in the UI server . Since this service will receive lots of data from many different client servers , we can segregate the data to be published into separate topics (for eg . NSE_NIFTY_50 , BSE_SENSEX , etc)

# UI Server
The UI Server is responsible for subscribing the data from the message broker and sending it back to the client's who requested for the data related to that particular security . This server will consist an http server to listen to incoming requests made by the client to add/remove items from a watchlist . This server will also send the data for that particular token from a particular exchange to every user that wants it . 



The communication between the Exchange servers and the Client servers will happen with the help of websockets . Also , the communication between the clients and the UI Servers will happen with the help of web sockets . The request to add / remove a particular stock to the watchlist would be an http request . 

This system shoud be able to handle upto 10 lakh customers . If we need to increase the capacity , we can horizontally scale and add more UI servers which would use the message broking service and cater increasing number of client requests .  We will also make use of a load balancer gateway that will route the incoming client requests to the appropriate UI Server that has the minimum amount of load . 


#
