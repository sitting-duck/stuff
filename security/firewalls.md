
Typically place in a network where we see the level of trust change.

Based mostly on examining the packets that are coming in over the network. 

### Packet Filtering
oldest and simplest firewall tech. Looks at the contents of each packet individually and determines based on the source and destination IP addresses, the port number, and the protocol being used, of whether the traffic will be allowed to pass. 

Attacks can slip by bc each packet is examined individually and not in concert with all the other packets.

### Stateful Packet Inspection
eg. Stateful firewalls, 
these function on the same general level as packet filtering firewalss, but they are able to keep track of the traffic at a granular level. 
A stateful firewall is able to watch the traffic over a given connection, generally defined by the source and destination IP addresses, the ports being used, and the already existing network traffic. 

It uses a state table to keep track of the connection state  and will only allow traffic through that is part of a new or already established connection. 

### Deep Packet Inspection
Deep Packet inspection firewalls can actually reassemble the contents of the traffic to look at what will be delivered to the application for which it is ultimately destined. 

Although is has great promise for blocking a lerge number of attacks, it is slower and introduces some delay. 
Additionally the question of privacy is also raised. Somebody in control of a deep packet inspection device could read every one of our email messages, see every web page exactly as we saw it, and easily listen in on our instant messaging conversations. 

### Proxy Servers
Ultimately a specialized variant of a firewall. These servers provide security and performance features, generally for a particular application ,such as mail or web browsing. Proxy servers can serve as a choke point in rder to allow us to filter traffic for attacks or undesirable content such as malware or traffic to web sites hosting adult content. 
They allow us to log the traffic that goes through them for later inspection, and they server to provide a layer of security for the devices behind them, by serving as a single source for requests. 

### DMZ 
DMZ, ie. a demilitarized zone is generally a combination of a network design feature and a protective device such as a firewall. 
Generally a combo of a network design feature and a protective device such as a firewall. 

### Network Intrusion Detection Systems
Place the NIDS behind a firewall that can filter for dumb traffic first so it doesn't get overloaded. 
Since the amount of traffic can be large, it can really only do a cursory inspection of the traffic, so it may miss some kinds of attaches. 

### IDS Detection Methods
Usually classified by the way they detect attacks. Divided into two main categories. 
Signature based detection and anomaly based detection. 

Signature based IDS work in a very similar fashion to most antivirus systems. They maintain a database of the signatures that might signal a particular type of attack and compare incoming traffic to those signatures. In general, this method works well, except when we encounter an attach that is new, or has been specifically constructed in order to not match existimng attack signatures. 


Anomaly based detection typically work by taking a baseline of the normal traffic. They can measure the present state of traffic on the network against the baseline in order to detect patterns that are not present in the traffic normally. These work considerably better than signature based detection for detecting new attacks but they have larger numbers of false positives. 




