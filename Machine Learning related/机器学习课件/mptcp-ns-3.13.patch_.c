Binary files old/ns-3.13/src/applications/bindings/callbacks_list.pyc and new/ns-3.13/src/applications/bindings/callbacks_list.pyc differ
Binary files old/ns-3.13/src/applications/bindings/modulegen_customizations.pyc and new/ns-3.13/src/applications/bindings/modulegen_customizations.pyc differ
Binary files old/ns-3.13/src/applications/bindings/modulegen__gcc_ILP32.pyc and new/ns-3.13/src/applications/bindings/modulegen__gcc_ILP32.pyc differ
diff -crBN old/ns-3.13/src/applications/helper/mp-tcp-packet-sink-helper.cc new/ns-3.13/src/applications/helper/mp-tcp-packet-sink-helper.cc
*** old/ns-3.13/src/applications/helper/mp-tcp-packet-sink-helper.cc	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/applications/helper/mp-tcp-packet-sink-helper.cc	2012-11-07 11:54:12.509495000 +0100
***************
*** 0 ****
--- 1,77 ----
+ /* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
+ /*
+  * Copyright (c) 2008 INRIA
+  *
+  * This program is free software; you can redistribute it and/or modify
+  * it under the terms of the GNU General Public License version 2 as
+  * published by the Free Software Foundation;
+  *
+  * This program is distributed in the hope that it will be useful,
+  * but WITHOUT ANY WARRANTY; without even the implied warranty of
+  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+  * GNU General Public License for more details.
+  *
+  * You should have received a copy of the GNU General Public License
+  * along with this program; if not, write to the Free Software
+  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
+  *
+  * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
+  */
+ 
+ #include "mp-tcp-packet-sink-helper.h"
+ #include "ns3/string.h"
+ #include "ns3/inet-socket-address.h"
+ #include "ns3/names.h"
+ #include "ns3/mp-tcp-packet-sink.h"
+ 
+ namespace ns3 {
+ 
+ MpTcpPacketSinkHelper::MpTcpPacketSinkHelper (std::string protocol, Address address, uint32_t algopr)
+ {
+   m_factory.SetTypeId ("ns3::MpTcpPacketSink");
+   m_factory.Set ("Protocol", StringValue (protocol));
+   m_factory.Set ("Local", AddressValue (address));
+   m_factory.Set ("algopr", UintegerValue (algopr));
+ }
+ 
+ void 
+ MpTcpPacketSinkHelper::SetAttribute (std::string name, const AttributeValue &value)
+ {
+   m_factory.Set (name, value);
+ }
+ 
+ ApplicationContainer
+ MpTcpPacketSinkHelper::Install (Ptr<Node> node) const
+ {
+   return ApplicationContainer (InstallPriv (node));
+ }
+ 
+ ApplicationContainer
+ MpTcpPacketSinkHelper::Install (std::string nodeName) const
+ {
+   Ptr<Node> node = Names::Find<Node> (nodeName);
+   return ApplicationContainer (InstallPriv (node));
+ }
+ 
+ ApplicationContainer
+ MpTcpPacketSinkHelper::Install (NodeContainer c) const
+ {
+   ApplicationContainer apps;
+   for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
+     {
+       apps.Add (InstallPriv (*i));
+     }
+ 
+   return apps;
+ }
+ 
+ Ptr<Application>
+ MpTcpPacketSinkHelper::InstallPriv (Ptr<Node> node) const
+ {
+   Ptr<Application> app = m_factory.Create<Application> ();
+   node->AddApplication (app);
+ 
+   return app;
+ }
+ 
+ } // namespace ns3
diff -crBN old/ns-3.13/src/applications/helper/mp-tcp-packet-sink-helper.h new/ns-3.13/src/applications/helper/mp-tcp-packet-sink-helper.h
*** old/ns-3.13/src/applications/helper/mp-tcp-packet-sink-helper.h	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/applications/helper/mp-tcp-packet-sink-helper.h	2012-11-07 11:43:21.649499000 +0100
***************
*** 0 ****
--- 1,92 ----
+ /* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
+ /*
+  * Copyright (c) 2008 INRIA
+  *
+  * This program is free software; you can redistribute it and/or modify
+  * it under the terms of the GNU General Public License version 2 as
+  * published by the Free Software Foundation;
+  *
+  * This program is distributed in the hope that it will be useful,
+  * but WITHOUT ANY WARRANTY; without even the implied warranty of
+  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+  * GNU General Public License for more details.
+  *
+  * You should have received a copy of the GNU General Public License
+  * along with this program; if not, write to the Free Software
+  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
+  *
+  * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
+  */
+ #ifndef MP_TCP_PACKET_SINK_HELPER_H
+ #define MP_TCP_PACKET_SINK_HELPER_H
+ 
+ #include "ns3/object-factory.h"
+ #include "ns3/ipv4-address.h"
+ #include "ns3/node-container.h"
+ #include "ns3/application-container.h"
+ 
+ namespace ns3 {
+ 
+ /**
+  * \brief A helper to make it easier to instantiate an ns3::PacketSinkApplication
+  * on a set of nodes.
+  */
+ class MpTcpPacketSinkHelper
+ {
+ public:
+   /**
+    * Create a MpTcpPacketSinkHelper to make it easier to work with PacketSinkApplications
+    *
+    * \param protocol the name of the protocol to use to receive traffic
+    *        This string identifies the socket factory type used to create
+    *        sockets for the applications.  A typical value would be 
+    *        ns3::TcpSocketFactory.
+    * \param address the address of the sink,
+    *
+    */
+   MpTcpPacketSinkHelper (std::string protocol, Address address, uint32_t algopr);
+ 
+   /**
+    * Helper function used to set the underlying application attributes.
+    *
+    * \param name the name of the application attribute to set
+    * \param value the value of the application attribute to set
+    */
+   void SetAttribute (std::string name, const AttributeValue &value);
+ 
+   /**
+    * Install an ns3::PacketSinkApplication on each node of the input container
+    * configured with all the attributes set with SetAttribute.
+    *
+    * \param c NodeContainer of the set of nodes on which a PacketSinkApplication 
+    * will be installed.
+    */
+   ApplicationContainer Install (NodeContainer c) const;
+ 
+   /**
+    * Install an ns3::PacketSinkApplication on each node of the input container
+    * configured with all the attributes set with SetAttribute.
+    *
+    * \param node The node on which a PacketSinkApplication will be installed.
+    */
+   ApplicationContainer Install (Ptr<Node> node) const;
+ 
+   /**
+    * Install an ns3::PacketSinkApplication on each node of the input container
+    * configured with all the attributes set with SetAttribute.
+    *
+    * \param nodeName The name of the node on which a PacketSinkApplication will be installed.
+    */
+   ApplicationContainer Install (std::string nodeName) const;
+ 
+ private:
+   /**
+    * \internal
+    */
+   Ptr<Application> InstallPriv (Ptr<Node> node) const;
+   ObjectFactory m_factory;
+ };
+ 
+ } // namespace ns3
+ 
+ #endif /* MP_TCP_PACKET_SINK_HELPER_H */
diff -crBN old/ns-3.13/src/applications/model/mp-tcp-packet-sink.cc new/ns-3.13/src/applications/model/mp-tcp-packet-sink.cc
*** old/ns-3.13/src/applications/model/mp-tcp-packet-sink.cc	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/applications/model/mp-tcp-packet-sink.cc	2012-11-07 12:39:30.633495000 +0100
***************
*** 0 ****
--- 1,209 ----
+ #include "ns3/address.h"
+ #include "ns3/address-utils.h"
+ #include "ns3/log.h"
+ #include "ns3/inet-socket-address.h"
+ #include "ns3/node.h"
+ #include "ns3/socket.h"
+ #include "ns3/udp-socket.h"
+ #include "ns3/simulator.h"
+ #include "ns3/socket-factory.h"
+ #include "ns3/packet.h"
+ #include "ns3/trace-source-accessor.h"
+ #include "ns3/udp-socket-factory.h"
+ 
+ #include "mp-tcp-packet-sink.h"
+ 
+ using namespace std;
+ 
+ namespace ns3 {
+ 
+ NS_LOG_COMPONENT_DEFINE ("MpTcpPacketSink");
+ NS_OBJECT_ENSURE_REGISTERED (MpTcpPacketSink);
+ 
+ TypeId
+ MpTcpPacketSink::GetTypeId (void)
+ {
+   static TypeId tid = TypeId ("ns3::MpTcpPacketSink")
+     .SetParent<Application> ()
+     .AddConstructor<MpTcpPacketSink> ()
+     .AddAttribute ("Local", "The Address on which to Bind the rx socket.",
+                    AddressValue (),
+                    MakeAddressAccessor (&MpTcpPacketSink::m_local),
+                    MakeAddressChecker ())
+     .AddAttribute ("Protocol", "The type id of the protocol to use for the rx socket.",
+                    TypeIdValue (TcpSocketFactory::GetTypeId ()),
+                    MakeTypeIdAccessor (&MpTcpPacketSink::m_tid),
+                    MakeTypeIdChecker ())
+     .AddAttribute ("algopr", "The used algorithm to handle pakcet reordering.",
+                    UintegerValue(0),
+                    MakeUintegerAccessor(&MpTcpPacketSink::algopr),
+                    MakeUintegerChecker<uint32_t>())
+     .AddTraceSource ("Rx", "A packet has been received",
+                      MakeTraceSourceAccessor (&MpTcpPacketSink::m_rxTrace))
+     ;
+   return tid;
+ }
+ 
+ MpTcpPacketSink::MpTcpPacketSink ()
+ {
+   NS_LOG_FUNCTION (this);
+   m_socket = 0;
+   m_totalRx = 0;
+ }
+ 
+ MpTcpPacketSink::~MpTcpPacketSink()
+ {
+   NS_LOG_FUNCTION (this);
+ }
+ 
+ uint32_t MpTcpPacketSink::GetTotalRx() const
+ {
+   return m_totalRx;
+ }
+ 
+ void MpTcpPacketSink::DoDispose (void)
+ {
+   NS_LOG_FUNCTION (this);
+   m_socket = 0;
+ 
+   // chain up
+   Application::DoDispose ();
+ }
+ 
+ // Application Methods
+ void MpTcpPacketSink::StartApplication()    // Called at time specified by Start
+ {
+   NS_LOG_FUNCTION (this);
+   // Create the socket if not already
+   if (!m_socket)
+     {
+       size  = 2000;
+       buf = new uint8_t[size];
+       m_socket = new MpTcpSocketBase(GetNode());
+       //m_socket = Socket::CreateSocket (GetNode(), m_tid);
+       m_socket->Bind (m_local);
+       m_socket->Listen ();
+       if (addressUtils::IsMulticast (m_local))
+       {
+           Ptr<UdpSocket> udpSocket = DynamicCast<UdpSocket> (m_socket);
+           if (udpSocket)
+           {
+               // equivalent to setsockopt (MCAST_JOIN_GROUP)
+               udpSocket->MulticastJoinGroup (0, m_local);
+           }
+           else
+           {
+               NS_FATAL_ERROR ("Error: joining multicast on a non-UDP socket");
+           }
+       }
+     }
+   m_socket->allocateRecvingBuffer(14000);
+   m_socket->SetunOrdBufMaxSize(2000);
+   m_socket->SetRecvCallback   ( MakeCallback(&MpTcpPacketSink::HandleRead, this) );
+   m_socket->SetAcceptCallback ( MakeNullCallback<bool, Ptr<Socket>, const Address &> (), MakeCallback(&MpTcpPacketSink::HandleAccept, this));
+   m_socket->SetCloseCallbacks ( MakeCallback(&MpTcpPacketSink::HandlePeerClose, this), MakeCallback(&MpTcpPacketSink::HandlePeerError, this));
+ 
+   m_socket->SetPacketReorderAlgo ( (PacketReorder_t) algopr);
+ }
+ 
+ void MpTcpPacketSink::StopApplication()     // Called at time specified by Stop
+ {
+   NS_LOG_FUNCTION (this);
+     NS_LOG_WARN ("MpTcpPacketSink -> Total received bytes " << m_totalRx);
+   while(!m_socketList.empty()) //these are accepted sockets, close them
+   {
+     Ptr<Socket> acceptedSocket = m_socketList.front();
+     m_socketList.pop_front();
+     acceptedSocket->Close();
+   }
+ 
+   if (m_socket)
+     {
+       m_socket->Close ();
+       m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
+     }
+ }
+ 
+ void MpTcpPacketSink::HandleRead (Ptr<Socket> socket)
+ {
+   NS_LOG_FUNCTION (this << m_socket);
+ 
+   uint32_t dataAmount = m_socket->Recv (buf, size);
+   m_totalRx += dataAmount;
+   NS_LOG_INFO ("MpTcpPacketSink::HandleRead() -> Received " << dataAmount << " bytes total Rx " << m_totalRx);
+ }
+ 
+ void MpTcpPacketSink::HandlePeerClose (Ptr<Socket> socket)
+ {
+   NS_LOG_INFO("MpTcpPktSink, peerClose");
+ }
+ 
+ void MpTcpPacketSink::HandlePeerError (Ptr<Socket> socket)
+ {
+   NS_LOG_INFO("MpTcpPktSink, peerError");
+ }
+ 
+ void MpTcpPacketSink::HandleAccept (Ptr<Socket> s, const Address& from)
+ {
+   NS_LOG_FUNCTION (this << s << from);
+   NS_LOG_INFO("MpTcpPktSink, connection accepted");
+   s->SetRecvCallback (MakeCallback(&MpTcpPacketSink::HandleRead, this));
+   m_socketList.push_back (s);
+ }
+ 
+ Ptr<MpTcpSocketBase>
+ MpTcpPacketSink::getMpTcpSocket ()
+ {
+     return m_socket;
+ }
+ 
+ /*
+ NS_LOG_COMPONENT_DEFINE ("MpTcpPacketSource");
+ NS_OBJECT_ENSURE_REGISTERED (MpTcpPacketSource);
+ 
+ TypeId
+ MpTcpPacketSource::GetTypeId (void)
+ {
+     static TypeId tid = TypeId("ns3::MpTcpPacketSource")
+         .SetParent<Application>()
+         .AddConstructor<MpTcpPacketSource>()
+         .AddAttribute ("Protocol", "The type id of the protocol to use for the tx socket",
+                        TypeIdValue (TcpSocketFactory::GetTypeId()),
+                        MakeTypeIdAccessor (&MpTcpPacketSource::m_tid),
+                        MakeTypeIdChecker ())
+         .AddAttribute ("ServerAddr", "The addres of the server",
+                        AddressValue(),
+                        MakeAddressAccessor (&MpTcpPacketSource::m_servAddr),
+                        MakeAddressChecker())
+         ;
+     return tid;
+ }
+ MpTcpPacketSource::MpTcpPacketSource()
+ {
+     NS_LOG_FUNCTION (this);
+ }
+ MpTcpPacketSource::~MpTcpPacketSource()
+ {
+     NS_LOG_FUNCTION (this);
+ }
+ void
+ MpTcpPacketSource::SetServPort(uint32_t port)
+ {
+     NS_LOG_FUNCTION (this << port);
+     m_servPort = port;
+ }
+ uint32_t
+ MpTcpPacketSource::GetServPort(void)
+ {
+     return m_servPort;
+ }
+ void
+ MpTcpPacketSource::StartApplication ()
+ {
+     NS_LOG_FUNCTION (this);
+     m_socket = Socket::CreateSocket(GetNode(), TcpSocketFactory::GetTypeId());
+     m_socket->Bind();
+ 
+ }
+ */
+ } // Namespace ns3
diff -crBN old/ns-3.13/src/applications/model/mp-tcp-packet-sink.h new/ns-3.13/src/applications/model/mp-tcp-packet-sink.h
*** old/ns-3.13/src/applications/model/mp-tcp-packet-sink.h	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/applications/model/mp-tcp-packet-sink.h	2012-11-07 09:26:37.009497000 +0100
***************
*** 0 ****
--- 1,80 ----
+ #ifndef __mp_tcp_packet_sink_h__
+ #define __mp_tcp_packet_sink_h__
+ 
+ #include "ns3/application.h"
+ #include "ns3/event-id.h"
+ #include "ns3/ptr.h"
+ #include "ns3/traced-callback.h"
+ #include "ns3/address.h"
+ #include "ns3/mp-tcp-socket-base.h"
+ #include "ns3/tcp-typedefs.h"
+ 
+ namespace ns3 {
+ 
+ class Address;
+ class Socket;
+ class Packet;
+ 
+ class MpTcpPacketSink   : public Application
+ {
+ public:
+   static TypeId GetTypeId (void);
+   MpTcpPacketSink ();
+ 
+   virtual ~MpTcpPacketSink ();
+ 
+   // Return the total bytes received in this sink app
+   uint32_t GetTotalRx() const;
+   Ptr<MpTcpSocketBase> getMpTcpSocket ();
+ 
+ protected:
+   virtual void DoDispose (void);
+ private:
+   // inherited from Application base class.
+   virtual void StartApplication (void);    // Called at time specified by Start
+   virtual void StopApplication (void);     // Called at time specified by Stop
+ 
+   void HandleRead   (Ptr<Socket>);
+   void HandleAccept (Ptr<Socket>, const Address& from);
+   void HandlePeerClose (Ptr<Socket>);
+   void HandlePeerError (Ptr<Socket>);
+ 
+   // In the case of TCP, each socket accept returns a new socket, so the
+   // listening socket is stored seperately from the accepted sockets
+   Ptr<MpTcpSocketBase>     m_socket;       // Listening socket
+   //Ptr<Socket> m_socket;
+   std::list<Ptr<Socket> > m_socketList; //the accepted sockets
+ 
+   Address         m_local;        // Local address to bind to
+   uint32_t        m_totalRx;      // Total bytes received
+   TypeId          m_tid;          // Protocol TypeId
+   uint32_t        size;
+   uint8_t *       buf;
+   TracedCallback<Ptr<const Packet>, const Address &> m_rxTrace;
+   uint32_t        algopr; // PacketReorder_t
+ };
+ 
+ /*
+ class MpTcpPacketSource : public Application
+ {
+ public:
+     static TypeId GetTypeId (void);
+     MpTcpPacketSource ();
+ 
+     virtual ~MpTcpPacketSource();
+ 
+     uint32_t m_servPort;
+     Ipv4Address  m_servAddr;
+ 
+ private:
+     virtual void StartApplication (void);
+     virtual void StopApplication (void);
+     TypeId  m_tid;          // Protocol TypeId
+     Ptr<Socket> m_socket;
+ 
+ };
+ */
+ } // namespace ns3
+ 
+ #endif
+ 
diff -crBN old/ns-3.13/src/applications/wscript new/ns-3.13/src/applications/wscript
*** old/ns-3.13/src/applications/wscript	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/applications/wscript	2012-11-07 11:11:40.569497000 +0100
***************
*** 18,23 ****
--- 18,25 ----
          'model/udp-echo-client.cc',
          'model/udp-echo-server.cc',
          'model/v4ping.cc',
+         'model/mp-tcp-packet-sink.cc',   #Pablo
+         'helper/mp-tcp-packet-sink-helper.cc', #Pablo
          'helper/bulk-send-helper.cc',
          'helper/on-off-helper.cc',
          'helper/packet-sink-helper.cc',
***************
*** 25,30 ****
--- 27,33 ----
          'helper/udp-client-server-helper.cc',
          'helper/udp-echo-helper.cc',
          'helper/v4ping-helper.cc',
+         
          ]
  
      applications_test = bld.create_ns3_module_test_library('applications')
***************
*** 50,55 ****
--- 53,60 ----
          'model/udp-echo-client.h',
          'model/udp-echo-server.h',
          'model/v4ping.h',
+         'model/mp-tcp-packet-sink.h', #Pablo
+         'helper/mp-tcp-packet-sink-helper.h', #Pablo
          'helper/bulk-send-helper.h',
          'helper/on-off-helper.h',
          'helper/packet-sink-helper.h',
***************
*** 57,62 ****
--- 62,68 ----
          'helper/udp-client-server-helper.h',
          'helper/udp-echo-helper.h',
          'helper/v4ping-helper.h',
+         
          ]
  
      bld.ns3_python_bindings()
Binary files old/ns-3.13/src/internet/bindings/callbacks_list.pyc and new/ns-3.13/src/internet/bindings/callbacks_list.pyc differ
Binary files old/ns-3.13/src/internet/bindings/modulegen__gcc_ILP32.pyc and new/ns-3.13/src/internet/bindings/modulegen__gcc_ILP32.pyc differ
diff -crBN old/ns-3.13/src/internet/helper/internet-stack-helper.cc new/ns-3.13/src/internet/helper/internet-stack-helper.cc
*** old/ns-3.13/src/internet/helper/internet-stack-helper.cc	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/helper/internet-stack-helper.cc	2012-11-27 13:18:56.516834000 +0100
***************
*** 291,298 ****
  void 
  InternetStackHelper::SetRoutingHelper (const Ipv4RoutingHelper &routing)
  {
!   delete m_routing;
!   m_routing = routing.Copy ();
  }
  
  void
--- 293,300 ----
  void 
  InternetStackHelper::SetRoutingHelper (const Ipv4RoutingHelper &routing)
  {
! 	delete m_routing;
! 	m_routing = routing.Copy ();
  }
  
  void
***************
*** 357,363 ****
      {
        if (node->GetObject<Ipv4> () != 0)
          {
!           NS_FATAL_ERROR ("InternetStackHelper::Install (): Aggregating " 
                            "an InternetStack to a node with an existing Ipv4 object");
            return;
          }
--- 359,365 ----
      {
        if (node->GetObject<Ipv4> () != 0)
          {
!           NS_FATAL_ERROR ("InternetStackHelper::Install (): Aggregating "
                            "an InternetStack to a node with an existing Ipv4 object");
            return;
          }
***************
*** 366,374 ****
        CreateAndAggregateObjectFromTypeId (node, "ns3::Ipv4L3Protocol");
        CreateAndAggregateObjectFromTypeId (node, "ns3::Icmpv4L4Protocol");
        CreateAndAggregateObjectFromTypeId (node, "ns3::UdpL4Protocol");
!       node->AggregateObject (m_tcpFactory.Create<Object> ());
        Ptr<PacketSocketFactory> factory = CreateObject<PacketSocketFactory> ();
        node->AggregateObject (factory);
        // Set routing
        Ptr<Ipv4> ipv4 = node->GetObject<Ipv4> ();
        Ptr<Ipv4RoutingProtocol> ipv4Routing = m_routing->Create (node);
--- 368,381 ----
        CreateAndAggregateObjectFromTypeId (node, "ns3::Ipv4L3Protocol");
        CreateAndAggregateObjectFromTypeId (node, "ns3::Icmpv4L4Protocol");
        CreateAndAggregateObjectFromTypeId (node, "ns3::UdpL4Protocol");
! 
!       Ptr<Object> tcp = m_tcpFactory.Create<Object> ();
! 
! 
!       node->AggregateObject (tcp);
        Ptr<PacketSocketFactory> factory = CreateObject<PacketSocketFactory> ();
        node->AggregateObject (factory);
+ 
        // Set routing
        Ptr<Ipv4> ipv4 = node->GetObject<Ipv4> ();
        Ptr<Ipv4RoutingProtocol> ipv4Routing = m_routing->Create (node);
diff -crBN old/ns-3.13/src/internet/helper/internet-stack-helper.h new/ns-3.13/src/internet/helper/internet-stack-helper.h
*** old/ns-3.13/src/internet/helper/internet-stack-helper.h	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/helper/internet-stack-helper.h	2012-11-27 13:18:19.354258000 +0100
***************
*** 1,4 ****
! /* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
  /*
   * Copyright (c) 2008 INRIA
   *
--- 1,4 ----
! 	/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
  /*
   * Copyright (c) 2008 INRIA
   *
diff -crBN old/ns-3.13/src/internet/model/ipv4-end-point.cc new/ns-3.13/src/internet/model/ipv4-end-point.cc
*** old/ns-3.13/src/internet/model/ipv4-end-point.cc	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/model/ipv4-end-point.cc	2012-11-16 11:32:13.102789000 +0100
***************
*** 107,113 ****
  }
  
  void 
! Ipv4EndPoint::ForwardUp (Ptr<Packet> p, const Ipv4Header& header, uint16_t sport,
                           Ptr<Ipv4Interface> incomingInterface)
  {
    if (!m_rxCallback.IsNull ())
--- 107,113 ----
  }
  
  void 
! Ipv4EndPoint::ForwardUp (Ptr<Packet> p, const Ipv4Header &header, uint16_t sport,
                           Ptr<Ipv4Interface> incomingInterface)
  {
    if (!m_rxCallback.IsNull ())
diff -crBN old/ns-3.13/src/internet/model/ipv4-l3-protocol.cc new/ns-3.13/src/internet/model/ipv4-l3-protocol.cc
*** old/ns-3.13/src/internet/model/ipv4-l3-protocol.cc	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/model/ipv4-l3-protocol.cc	2012-12-18 10:53:59.907904000 +0100
***************
*** 295,300 ****
--- 295,302 ----
  Ptr<Ipv4Interface>
  Ipv4L3Protocol::GetInterface (uint32_t index) const
  {
+   NS_LOG_FUNCTION (this << index);
+ 
    if (index < m_interfaces.size ())
      {
        return m_interfaces[index];
***************
*** 305,310 ****
--- 307,313 ----
  uint32_t 
  Ipv4L3Protocol::GetNInterfaces (void) const
  {
+   NS_LOG_FUNCTION (this);
    return m_interfaces.size ();
  }
  
***************
*** 312,317 ****
--- 315,321 ----
  Ipv4L3Protocol::GetInterfaceForAddress (
    Ipv4Address address) const
  {
+   NS_LOG_FUNCTION (this);
    int32_t interface = 0;
    for (Ipv4InterfaceList::const_iterator i = m_interfaces.begin (); 
         i != m_interfaces.end (); 
***************
*** 334,339 ****
--- 337,344 ----
    Ipv4Address address, 
    Ipv4Mask mask) const
  {
+ 
+   NS_LOG_FUNCTION (this);
    int32_t interface = 0;
    for (Ipv4InterfaceList::const_iterator i = m_interfaces.begin (); 
         i != m_interfaces.end (); 
***************
*** 355,360 ****
--- 359,365 ----
  Ipv4L3Protocol::GetInterfaceForDevice (
    Ptr<const NetDevice> device) const
  {
+ 	NS_LOG_FUNCTION (this);
    int32_t interface = 0;
    for (Ipv4InterfaceList::const_iterator i = m_interfaces.begin (); 
         i != m_interfaces.end (); 
***************
*** 437,443 ****
  {
    NS_LOG_FUNCTION (this << &device << p << protocol <<  from);
  
!   NS_LOG_LOGIC ("Packet from " << from << " received on node " << 
                  m_node->GetId ());
  
    uint32_t interface = 0;
--- 441,447 ----
  {
    NS_LOG_FUNCTION (this << &device << p << protocol <<  from);
  
!   NS_LOG_LOGIC ("Packet from " << from << " received on node " <<
                  m_node->GetId ());
  
    uint32_t interface = 0;
***************
*** 495,511 ****
      }
  
    NS_ASSERT_MSG (m_routingProtocol != 0, "Need a routing protocol object to process packets");
-   if (!m_routingProtocol->RouteInput (packet, ipHeader, device,
-                                       MakeCallback (&Ipv4L3Protocol::IpForward, this),
-                                       MakeCallback (&Ipv4L3Protocol::IpMulticastForward, this),
-                                       MakeCallback (&Ipv4L3Protocol::LocalDeliver, this),
-                                       MakeCallback (&Ipv4L3Protocol::RouteInputError, this)
-                                       ))
-     {
-       NS_LOG_WARN ("No route found for forwarding packet.  Drop.");
-       m_dropTrace (ipHeader, packet, DROP_NO_ROUTE, m_node->GetObject<Ipv4> (), interface);
-     }
  
  
  }
  
--- 499,515 ----
      }
  
    NS_ASSERT_MSG (m_routingProtocol != 0, "Need a routing protocol object to process packets");
  
+   if (!m_routingProtocol->RouteInput (packet, ipHeader, device,
+ 		  MakeCallback (&Ipv4L3Protocol::IpForward, this),
+ 		  MakeCallback (&Ipv4L3Protocol::IpMulticastForward, this),
+ 		  MakeCallback (&Ipv4L3Protocol::LocalDeliver, this),
+ 		  MakeCallback (&Ipv4L3Protocol::RouteInputError, this)
+   ))
+   {
+ 	  NS_LOG_WARN ("No route found for forwarding packet.  Drop.");
+ 	  m_dropTrace (ipHeader, packet, DROP_NO_ROUTE, m_node->GetObject<Ipv4> (), interface);
+   }
  
  }
  
***************
*** 899,904 ****
--- 903,909 ----
              {
                GetIcmp ()->SendDestUnreachPort (ip, copy);
              }
+           break;
          }
      }
  }
diff -crBN old/ns-3.13/src/internet/model/nsc-tcp-l4-protocol.cc new/ns-3.13/src/internet/model/nsc-tcp-l4-protocol.cc
*** old/ns-3.13/src/internet/model/nsc-tcp-l4-protocol.cc	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/model/nsc-tcp-l4-protocol.cc	2012-11-07 09:26:37.013498000 +0100
***************
*** 195,210 ****
        Ptr<Node>node = this->GetObject<Node> ();
        if (node != 0)
          {
!           Ptr<Ipv4L3Protocol> ipv4 = this->GetObject<Ipv4L3Protocol> ();
!           if (ipv4 != 0)
!             {
!               this->SetNode (node);
!               ipv4->Insert (this);
!               Ptr<NscTcpSocketFactoryImpl> tcpFactory = CreateObject<NscTcpSocketFactoryImpl> ();
!               tcpFactory->SetTcp (this);
!               node->AggregateObject (tcpFactory);
!               this->SetDownTarget (MakeCallback (&Ipv4L3Protocol::Send, ipv4));
!             }
          }
      }
    Object::NotifyNewAggregate ();
--- 196,212 ----
        Ptr<Node>node = this->GetObject<Node> ();
        if (node != 0)
          {
!     	  Ptr<Ipv4L3Protocol> ipv4 = this->GetObject<Ipv4L3Protocol> ();
! 
!     	  if (ipv4 != 0)
!     	  {
!     		  this->SetNode (node);
!     		  ipv4->Insert (this);
!     		  Ptr<NscTcpSocketFactoryImpl> tcpFactory = CreateObject<NscTcpSocketFactoryImpl> ();
!     		  tcpFactory->SetTcp (this);
!     		  node->AggregateObject (tcpFactory);
!     		  this->SetDownTarget (MakeCallback (&Ipv4L3Protocol::Send, ipv4)); ////David/Ramón --> Comment test (remember to undo) --> The is the only legacy code line
!     	  }
          }
      }
    Object::NotifyNewAggregate ();
***************
*** 352,357 ****
--- 354,361 ----
  
    NS_ASSERT (datalen > 20);
  
+   ////David/Ramón
+   NS_LOG_FUNCTION (this);
  
    // create packet, without IP header. The TCP header is not touched.
    // Not using the IP header makes integration easier, but it destroys
***************
*** 459,471 ****
  void
  NscTcpL4Protocol::SetDownTarget (Ipv4L4Protocol::DownTargetCallback callback)
  {
!   m_downTarget = callback;
  }
  
  Ipv4L4Protocol::DownTargetCallback
  NscTcpL4Protocol::GetDownTarget (void) const
  {
!   return m_downTarget;
  }
  
  } // namespace ns3
--- 463,475 ----
  void
  NscTcpL4Protocol::SetDownTarget (Ipv4L4Protocol::DownTargetCallback callback)
  {
! 	m_downTarget = callback;
  }
  
  Ipv4L4Protocol::DownTargetCallback
  NscTcpL4Protocol::GetDownTarget (void) const
  {
! 	return m_downTarget;
  }
  
  } // namespace ns3
diff -crBN old/ns-3.13/src/internet/model/rtt-estimator.cc new/ns-3.13/src/internet/model/rtt-estimator.cc
*** old/ns-3.13/src/internet/model/rtt-estimator.cc	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/model/rtt-estimator.cc	2012-12-18 11:00:38.904683000 +0100
***************
*** 30,35 ****
--- 30,38 ----
  #include "rtt-estimator.h"
  #include "ns3/simulator.h"
  #include "ns3/double.h"
+ #include "ns3/integer.h"
+ 
+ #include "ns3/log.h"
  
  namespace ns3 {
  
***************
*** 42,56 ****
    static TypeId tid = TypeId ("ns3::RttEstimator")
      .SetParent<Object> ()
      .AddAttribute ("MaxMultiplier", 
!                    "XXX",
!                    DoubleValue (64.0),
                     MakeDoubleAccessor (&RttEstimator::m_maxMultiplier),
!                    MakeDoubleChecker<double> ())
      .AddAttribute ("InitialEstimation", 
!                    "XXX",
                     TimeValue (Seconds (1.0)),
!                    MakeTimeAccessor (&RttEstimator::SetEstimate,
!                                      &RttEstimator::GetEstimate),
                     MakeTimeChecker ())
      .AddAttribute ("MinRTO", 
                     "Minimum retransmit timeout value",
--- 45,58 ----
    static TypeId tid = TypeId ("ns3::RttEstimator")
      .SetParent<Object> ()
      .AddAttribute ("MaxMultiplier", 
!                    "Maximum RTO Multiplier",
!                    IntegerValue (64),
                     MakeDoubleAccessor (&RttEstimator::m_maxMultiplier),
!                    MakeIntegerChecker<u_int16_t> ())
      .AddAttribute ("InitialEstimation", 
!                    "Initial RTT estimation",
                     TimeValue (Seconds (1.0)),
!                    MakeTimeAccessor (&RttEstimator::m_initialEstimatedRtt),
                     MakeTimeChecker ())
      .AddAttribute ("MinRTO", 
                     "Minimum retransmit timeout value",
***************
*** 65,86 ****
  void 
  RttEstimator::SetMinRto (Time minRto)
  {
!   minrto = minRto;
  }
  Time 
  RttEstimator::GetMinRto (void) const
  {
!   return Time (minrto);
  }
  void 
! RttEstimator::SetEstimate (Time estimate)
  {
!   est = estimate;
  }
  Time 
! RttEstimator::GetEstimate (void) const
  {
!   return Time (est);
  }
  
  
--- 67,88 ----
  void 
  RttEstimator::SetMinRto (Time minRto)
  {
!   m_minRto = minRto;
  }
  Time 
  RttEstimator::GetMinRto (void) const
  {
!   return Time (m_minRto);
  }
  void 
! RttEstimator::SetCurrentEstimate (Time estimate)
  {
!   m_currentEstimatedRtt = estimate;
  }
  Time 
! RttEstimator::GetCurrentEstimate (void) const
  {
!   return Time (m_currentEstimatedRtt);
  }
  
  
***************
*** 97,139 ****
  
  // Base class methods
  
! RttEstimator::RttEstimator () : next (1), history (),
!                                 nSamples (0), multiplier (1.0)
  { 
    //note next=1 everywhere since first segment will have sequence 1
  }
  
- RttEstimator::RttEstimator(const RttEstimator& c)
-   : Object (c), next (c.next), history (c.history),
-     m_maxMultiplier (c.m_maxMultiplier), est (c.est),
-     minrto (c.minrto), nSamples (c.nSamples),
-     multiplier (c.multiplier)
- {
- }
- 
  RttEstimator::~RttEstimator ()
  {
  }
  
! void RttEstimator::SentSeq (SequenceNumber32 s, uint32_t c)
  { // Note that a particular sequence has been sent
!   if (s == next)
      { // This is the next expected one, just log at end
!       history.push_back (RttHistory (s, c, Simulator::Now () ));
!       next = s + SequenceNumber32 (c); // Update next expected
      }
    else
      { // This is a retransmit, find in list and mark as re-tx
!       for (RttHistory_t::iterator i = history.begin (); i != history.end (); ++i)
          {
!           if ((s >= i->seq) && (s < (i->seq + SequenceNumber32 (i->count))))
              { // Found it
                i->retx = true;
                // One final test..be sure this re-tx does not extend "next"
!               if ((s + SequenceNumber32 (c)) > next)
                  {
!                   next = s + SequenceNumber32 (c);
!                   i->count = ((s + SequenceNumber32 (c)) - i->seq); // And update count in hist
                  }
                break;
              }
--- 99,137 ----
  
  // Base class methods
  
! RttEstimator::RttEstimator ()
!   : m_next (1), m_history (),
!     m_currentEstimatedRtt(m_initialEstimatedRtt),
!     m_minRto(Seconds(0.2)),  //Pablo UC
!     m_nSamples (0),
!     m_multiplier (1)
  { 
    //note next=1 everywhere since first segment will have sequence 1
  }
  
  RttEstimator::~RttEstimator ()
  {
  }
  
! void RttEstimator::SentSeq (SequenceNumber32 seq, uint32_t size)
  { // Note that a particular sequence has been sent
!   if (seq == m_next)
      { // This is the next expected one, just log at end
!       m_history.push_back (RttHistory (seq, size, Simulator::Now () ));
!       m_next = seq + SequenceNumber32 (size); // Update next expected
      }
    else
      { // This is a retransmit, find in list and mark as re-tx
!       for (RttHistory_t::iterator i = m_history.begin (); i != m_history.end (); ++i)
          {
!           if ((seq >= i->seq) && (seq < (i->seq + SequenceNumber32 (i->count))))
              { // Found it
                i->retx = true;
                // One final test..be sure this re-tx does not extend "next"
!               if ((seq + SequenceNumber32 (size)) > m_next)
                  {
!                   m_next = seq + SequenceNumber32 (size);
!                   i->count = ((seq + SequenceNumber32 (size)) - i->seq); // And update count in hist
                  }
                break;
              }
***************
*** 141,195 ****
      }
  }
  
! Time RttEstimator::AckSeq (SequenceNumber32 a)
  { // An ack has been received, calculate rtt and log this measurement
    // Note we use a linear search (O(n)) for this since for the common
    // case the ack'ed packet will be at the head of the list
    Time m = Seconds (0.0);
!   if (history.size () == 0) return (m);    // No pending history, just exit
!   RttHistory& h = history.front ();
!   if (!h.retx && a >= (h.seq + SequenceNumber32 (h.count)))
      { // Ok to use this sample
        m = Simulator::Now () - h.time; // Elapsed time
        Measurement (m);                // Log the measurement
        ResetMultiplier ();             // Reset multiplier on valid measurement
      }
    // Now delete all ack history with seq <= ack
!   while(history.size () > 0)
      {
!       RttHistory& h = history.front ();
!       if ((h.seq + SequenceNumber32 (h.count)) > a) break;               // Done removing
!       history.pop_front (); // Remove
      }
    return m;
  }
  
  void RttEstimator::ClearSent ()
  { // Clear all history entries
!   next = 1;
!   history.clear ();
  }
  
  void RttEstimator::IncreaseMultiplier ()
  {
!   multiplier = std::min (multiplier * 2.0, m_maxMultiplier);
  }
  
  void RttEstimator::ResetMultiplier ()
  {
!   multiplier = 1.0;
  }
  
  void RttEstimator::Reset ()
  { // Reset to initial state
!   next = 1;
!   est = 1; // XXX: we should go back to the 'initial value' here. Need to add support in Object for this.
!   history.clear ();         // Remove all info from the history
!   nSamples = 0;
    ResetMultiplier ();
  }
  
! 
  
  //-----------------------------------------------------------------------------
  //-----------------------------------------------------------------------------
--- 139,213 ----
      }
  }
  
! Time RttEstimator::AckSeq (SequenceNumber32 ackSeq)
  { // An ack has been received, calculate rtt and log this measurement
    // Note we use a linear search (O(n)) for this since for the common
    // case the ack'ed packet will be at the head of the list
    Time m = Seconds (0.0);
!   if (m_history.size () == 0) return (m);    // No pending history, just exit
!   RttHistory& h = m_history.front ();
!   if (!h.retx && ackSeq >= (h.seq + SequenceNumber32 (h.count)))
      { // Ok to use this sample
        m = Simulator::Now () - h.time; // Elapsed time
        Measurement (m);                // Log the measurement
        ResetMultiplier ();             // Reset multiplier on valid measurement
      }
    // Now delete all ack history with seq <= ack
!   while(m_history.size () > 0)
      {
!       RttHistory& h = m_history.front ();
!       if ((h.seq + SequenceNumber32 (h.count)) > ackSeq) break;               // Done removing
!       m_history.pop_front (); // Remove
      }
    return m;
  }
  
  void RttEstimator::ClearSent ()
  { // Clear all history entries
!   m_next = 1;
!   m_history.clear ();
  }
  
  void RttEstimator::IncreaseMultiplier ()
  {
!   m_multiplier = (m_multiplier*2 < m_maxMultiplier) ? m_multiplier*2 : m_maxMultiplier;
  }
  
  void RttEstimator::ResetMultiplier ()
  {
!   m_multiplier = 1;
  }
  
  void RttEstimator::Reset ()
  { // Reset to initial state
!   m_next = 1;
!   m_currentEstimatedRtt = m_initialEstimatedRtt;
!   m_history.clear ();         // Remove all info from the history
!   m_nSamples = 0;
    ResetMultiplier ();
  }
  
! void
! RttEstimator:: pktRetransmit (SequenceNumber32 seq)
! {
!     std::deque<RttHistory>::iterator current = m_history.begin();
!     std::deque<RttHistory>::iterator next = m_history.begin();
!     while(next != m_history.end())
!     {
!         current = next;
!         if ((*current).seq == seq)
!         {
!             m_history.erase(current);
!             /**
!              * because the corresponding packet have been retransmitted we preffer to not take into acount its RTT because we can't
!              * differenciate between the case where the received ack is for the first segment or the retransmitted one
!              */
!             //(*it).time = Simulator::Now();
!             break;
!         }
!         ++next;
!     }
! }
  
  //-----------------------------------------------------------------------------
  //-----------------------------------------------------------------------------
***************
*** 204,258 ****
      .SetParent<RttEstimator> ()
      .AddConstructor<RttMeanDeviation> ()
      .AddAttribute ("Gain",
!                    "XXX",
                     DoubleValue (0.1),
!                    MakeDoubleAccessor (&RttMeanDeviation::gain),
                     MakeDoubleChecker<double> ())
    ;
    return tid;
  }
  
  RttMeanDeviation::RttMeanDeviation() :
!   variance (0) 
  { 
  }
  
  RttMeanDeviation::RttMeanDeviation (const RttMeanDeviation& c)
!   : RttEstimator (c), gain (c.gain), variance (c.variance)
  {
  }
  
  void RttMeanDeviation::Measurement (Time m)
  {
!   if (nSamples)
      { // Not first
!       int64x64_t err = m - est;
!       est = est + gain * err;         // estimated rtt
!       variance = variance + gain * (Abs (err) - variance); // variance of rtt
      }
    else
      { // First sample
!       est = m;                        // Set estimate to current
        //variance = sample / 2;               // And variance to current / 2
!       variance = m; // try this
      }
!   nSamples++;
  }
  
  Time RttMeanDeviation::RetransmitTimeout ()
  {
!   // If not enough samples, justjust return 2 times estimate
    //if (nSamples < 2) return est * 2;
    int64x64_t retval;
!   if (variance < est / 4.0)
      {
!       retval = est * 2 * multiplier;            // At least twice current est
      }
    else
      {
!       retval = (est + 4 * variance) * multiplier; // As suggested by Jacobson
      }
!   retval = Max (retval, minrto);
    return Time (retval);
  }
  
--- 222,276 ----
      .SetParent<RttEstimator> ()
      .AddConstructor<RttMeanDeviation> ()
      .AddAttribute ("Gain",
!                    "Gain used in estimating the RTT, must be 0 < Gain < 1",
                     DoubleValue (0.1),
!                    MakeDoubleAccessor (&RttMeanDeviation::m_gain),
                     MakeDoubleChecker<double> ())
    ;
    return tid;
  }
  
  RttMeanDeviation::RttMeanDeviation() :
!   m_variance (0) 
  { 
  }
  
  RttMeanDeviation::RttMeanDeviation (const RttMeanDeviation& c)
!   : RttEstimator (c), m_gain (c.m_gain), m_variance (c.m_variance)
  {
  }
  
  void RttMeanDeviation::Measurement (Time m)
  {
!   if (m_nSamples)
      { // Not first
!       Time err(m - m_currentEstimatedRtt);
!       m_currentEstimatedRtt += m_gain * err;  // estimated rtt
!       m_variance += m_gain * (Abs (err) - m_variance);   // variance of rtt
      }
    else
      { // First sample
!       m_currentEstimatedRtt = m;             // Set estimate to current
        //variance = sample / 2;               // And variance to current / 2
!       m_variance = m; // try this
      }
!   m_nSamples++;
  }
  
  Time RttMeanDeviation::RetransmitTimeout ()
  {
!   // If not enough samples, just return 2 times estimate
    //if (nSamples < 2) return est * 2;
    int64x64_t retval;
!   if (m_variance < m_currentEstimatedRtt / 4.0)
      {
!       retval = m_currentEstimatedRtt * 2 * m_multiplier;            // At least twice current est
      }
    else
      {
!       retval = (m_currentEstimatedRtt + 4 * m_variance) * m_multiplier; // As suggested by Jacobson
      }
!   retval = Max (retval, m_minRto);
    return Time (retval);
  }
  
***************
*** 263,269 ****
  
  void RttMeanDeviation::Reset ()
  { // Reset to initial state
!   variance = 0;
    RttEstimator::Reset ();
  }
  } //namepsace ns3
--- 281,293 ----
  
  void RttMeanDeviation::Reset ()
  { // Reset to initial state
!   m_variance = 0;
    RttEstimator::Reset ();
  }
+ void RttMeanDeviation::Gain (double g)
+ {
+   NS_ASSERT_MSG( (g > 0) && (g < 1), "RttMeanDeviation: Gain must be less than 1 and greater than 0" );
+   m_gain = g;
+ }
+ 
  } //namepsace ns3
diff -crBN old/ns-3.13/src/internet/model/rtt-estimator.h new/ns-3.13/src/internet/model/rtt-estimator.h
*** old/ns-3.13/src/internet/model/rtt-estimator.h	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/model/rtt-estimator.h	2012-11-20 10:06:43.809681000 +0100
***************
*** 35,48 ****
  /**
   * \ingroup tcp
   *
!  * \brief Implements several variations of round trip time estimators
   */
  class RttHistory {
  public:
    RttHistory (SequenceNumber32 s, uint32_t c, Time t);
    RttHistory (const RttHistory& h); // Copy constructor
  public:
!   SequenceNumber32  seq;    // First sequence number in packet sent
    uint32_t        count;  // Number of bytes sent
    Time            time;   // Time this one was sent
    bool            retx;   // True if this has been retransmitted
--- 35,48 ----
  /**
   * \ingroup tcp
   *
!  * \brief Helper class to store RTT measurements
   */
  class RttHistory {
  public:
    RttHistory (SequenceNumber32 s, uint32_t c, Time t);
    RttHistory (const RttHistory& h); // Copy constructor
  public:
!   SequenceNumber32  seq;  // First sequence number in packet sent
    uint32_t        count;  // Number of bytes sent
    Time            time;   // Time this one was sent
    bool            retx;   // True if this has been retransmitted
***************
*** 50,117 ****
  
  typedef std::deque<RttHistory> RttHistory_t;
  
! class RttEstimator : public Object {  //  Base class for all RTT Estimators
  public:
    static TypeId GetTypeId (void);
  
    RttEstimator();
-   RttEstimator(const RttEstimator&); // Copy constructor
    virtual ~RttEstimator();
  
!   virtual void SentSeq (SequenceNumber32, uint32_t);
!   virtual Time AckSeq (SequenceNumber32);
    virtual void ClearSent ();
!   virtual void   Measurement (Time t) = 0;
    virtual Time RetransmitTimeout () = 0;
!   void Init (SequenceNumber32 s) { next = s; }
    virtual Ptr<RttEstimator> Copy () const = 0;
    virtual void IncreaseMultiplier ();
    virtual void ResetMultiplier ();
    virtual void Reset ();
  
    void SetMinRto (Time minRto);
    Time GetMinRto (void) const;
!   void SetEstimate (Time estimate);
!   Time GetEstimate (void) const;
  
  private:
!   SequenceNumber32        next;    // Next expected sequence to be sent
!   RttHistory_t history; // List of sent packet
!   double m_maxMultiplier;
! public:
!   int64x64_t       est;     // Current estimate
!   int64x64_t       minrto; // minimum value of the timeout
!   uint32_t      nSamples; // Number of samples
!   double       multiplier;   // RTO Multiplier
! };
  
- // The "Mean-Deviation" estimator, as discussed by Van Jacobson
- // "Congestion Avoidance and Control", SIGCOMM 88, Appendix A
  
! //Doc:Class Class {\tt RttMeanDeviation} implements the "Mean--Deviation" estimator
! //Doc:Class as described by Van Jacobson
! //Doc:Class "Congestion Avoidance and Control", SIGCOMM 88, Appendix A
  class RttMeanDeviation : public RttEstimator {
  public:
    static TypeId GetTypeId (void);
  
    RttMeanDeviation ();
  
  
!   //Doc:Method
!   RttMeanDeviation (const RttMeanDeviation&); // Copy constructor
!   //Doc:Desc Copy constructor.
!   //Doc:Arg1 {\tt RttMeanDeviation} object to copy.
! 
!   void Measurement (Time);
    Time RetransmitTimeout ();
    Ptr<RttEstimator> Copy () const;
    void Reset ();
-   void Gain (double g) { gain = g; }
  
! public:
!   double       gain;       // Filter gain
!   int64x64_t   variance;   // Current variance
  };
  } // namespace ns3
  
--- 50,205 ----
  
  typedef std::deque<RttHistory> RttHistory_t;
  
! /**
!  * \ingroup tcp
!  *
!  * \brief Base class for all RTT Estimators
!  */
! class RttEstimator : public Object {
  public:
    static TypeId GetTypeId (void);
  
    RttEstimator();
    virtual ~RttEstimator();
  
!   /**
!    * \brief Note that a particular sequence has been sent
!    * \param seq the packet sequence number.
!    * \param size the packet size.
!    */
!   virtual void SentSeq (SequenceNumber32 seq, uint32_t size);
! 
!   /**
!    * \brief Note that a particular ack sequence has been received
!    * \param ackSeq the ack sequence number.
!    * \return The measured RTT for this ack.
!    */
!   virtual Time AckSeq (SequenceNumber32 ackSeq);
! 
!   /**
!    * \brief Clear all history entries
!    */
    virtual void ClearSent ();
! 
!   /**
!    * \brief Add a new measurement to the estimator. Pure virtual function.
!    * \param t the new RTT measure.
!    */
!   virtual void  Measurement (Time t) = 0;
! 
!   /**
!    * \brief Returns the estimated RTO. Pure virtual function.
!    * \return the estimated RTO.
!    */
    virtual Time RetransmitTimeout () = 0;
! 
    virtual Ptr<RttEstimator> Copy () const = 0;
+ 
+   /**
+    * \brief Increase the estimation multiplier up to MaxMultiplier.
+    */
    virtual void IncreaseMultiplier ();
+ 
+   void Init (SequenceNumber32 s) { m_next = s; }
+ 
+   /**
+    * \brief Resets the estimation multiplier to 1.
+    */
    virtual void ResetMultiplier ();
+ 
+   /**
+    * \brief Resets the estimation to its initial state.
+    */
    virtual void Reset ();
  
+   /**
+    * \brief Sets the Minimum RTO.
+    * \param minRto The minimum RTO returned by the estimator.
+    */
    void SetMinRto (Time minRto);
+ 
+   /**
+    * \brief Get the Minimum RTO.
+    * \return The minimum RTO returned by the estimator.
+    */
    Time GetMinRto (void) const;
! 
!   /**
!    * \brief Sets the current RTT estimate (forcefully).
!    * \param estimate The current RTT estimate.
!    */
!   void SetCurrentEstimate (Time estimate);
! 
!   /**
!    * \brief gets the current RTT estimate.
!    * \return The current RTT estimate.
!    */
!   Time GetCurrentEstimate (void) const;
! 
!   void pktRetransmit (SequenceNumber32 seq);
  
  private:
!   SequenceNumber32 m_next;    // Next expected sequence to be sent
!   RttHistory_t m_history;     // List of sent packet
!   u_int16_t m_maxMultiplier;
!   Time m_initialEstimatedRtt;
  
  
! protected:
! 
!   int64x64_t   m_currentEstimatedRtt;     // Current estimate
!   int64x64_t   m_minRto;                  // minimum value of the timeout
!   uint32_t     m_nSamples;                // Number of samples
!   u_int16_t    m_multiplier;              // RTO Multiplier
! 
! };
! 
! /**
!  * \ingroup tcp
!  *
!  * \brief The "Mean--Deviation" RTT estimator, as discussed by Van Jacobson
!  *
!  * This class implements the "Mean--Deviation" RTT estimator, as discussed
!  * by Van Jacobson and Michael J. Karels, in
!  * "Congestion Avoidance and Control", SIGCOMM 88, Appendix A
!  *
!  */
  class RttMeanDeviation : public RttEstimator {
  public:
    static TypeId GetTypeId (void);
  
    RttMeanDeviation ();
  
+   RttMeanDeviation (const RttMeanDeviation&);
  
!   /**
!    * \brief Add a new measurement to the estimator.
!    * \param measure the new RTT measure.
!    */
!   void Measurement (Time measure);
! 
!   /**
!    * \brief Returns the estimated RTO.
!    * \return the estimated RTO.
!    */
    Time RetransmitTimeout ();
+ 
    Ptr<RttEstimator> Copy () const;
+ 
+   /**
+    * \brief Resets sthe estimator.
+    */
    void Reset ();
  
!   /**
!    * \brief Sets the estimator Gain.
!    * \param g the gain, where 0 < g < 1.
!    */
!   void Gain (double g);
! 
! private:
!   double       m_gain;       // Filter gain
!   int64x64_t   m_variance;   // Current variance
  };
  } // namespace ns3
  
diff -crBN old/ns-3.13/src/internet/model/tcp-l4-protocol.cc new/ns-3.13/src/internet/model/tcp-l4-protocol.cc
*** old/ns-3.13/src/internet/model/tcp-l4-protocol.cc	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/model/tcp-l4-protocol.cc	2012-12-14 11:26:49.869156000 +0100
***************
*** 35,41 ****
--- 35,43 ----
  #include "ipv4-end-point.h"
  #include "ipv4-l3-protocol.h"
  #include "tcp-socket-factory-impl.h"
+ #include "tcp-typedefs.h"       ////Pablo
  #include "tcp-newreno.h"
+ #include "tcp-reno.h"	        ////Pablo
  #include "rtt-estimator.h"
  
  #include <vector>
***************
*** 48,53 ****
--- 50,320 ----
  
  NS_OBJECT_ENSURE_REGISTERED (TcpL4Protocol);
  
+ 
+ //// Pablo (multipath)
+ //State Machine things --------------------------------------------------------
+ TcpStateMachine::TcpStateMachine()
+   : aT (LAST_STATE, StateActionVec_t(LAST_EVENT)),
+        eV (MAX_FLAGS)
+ {
+   NS_LOG_FUNCTION_NOARGS ();
+ 
+   // Create the state table
+   // Closed state
+   aT[CLOSED][APP_LISTEN]  = SA (LISTEN,   NO_ACT);
+   aT[CLOSED][APP_CONNECT] = SA (SYN_SENT, SYN_TX);
+   aT[CLOSED][APP_SEND]    = SA (CLOSED,   RST_TX);
+   aT[CLOSED][SEQ_RECV]    = SA (CLOSED,   NO_ACT);
+   aT[CLOSED][APP_CLOSE]   = SA (CLOSED,   NO_ACT);
+   aT[CLOSED][TIMEOUT]     = SA (CLOSED,   RST_TX);
+   aT[CLOSED][ACK_RX]      = SA (CLOSED,   RST_TX);
+   aT[CLOSED][SYN_RX]      = SA (CLOSED,   RST_TX);
+   aT[CLOSED][SYN_ACK_RX]  = SA (CLOSED,   RST_TX);
+   aT[CLOSED][FIN_RX]      = SA (CLOSED,   RST_TX);
+   aT[CLOSED][FIN_ACK_RX]  = SA (CLOSED,   RST_TX);
+   aT[CLOSED][RST_RX]      = SA (CLOSED,   CANCEL_TM);
+   aT[CLOSED][BAD_FLAGS]   = SA (CLOSED,   RST_TX);
+ 
+   // Listen State
+   // For the listen state, anything other than CONNECT or SEND
+   // is simply ignored....this likely indicates the child TCP
+   // has finished and issued unbind call, but the remote end
+   // has not yet  closed.
+   aT[LISTEN][APP_LISTEN]  = SA (LISTEN,   NO_ACT);
+   aT[LISTEN][APP_CONNECT] = SA (SYN_SENT, SYN_TX);
+   aT[LISTEN][APP_SEND]    = SA (SYN_SENT, SYN_TX);
+   aT[LISTEN][SEQ_RECV]    = SA (LISTEN,   NO_ACT);
+   aT[LISTEN][APP_CLOSE]   = SA (CLOSED,   NO_ACT);
+   aT[LISTEN][TIMEOUT]     = SA (LISTEN,   NO_ACT);
+   aT[LISTEN][ACK_RX]      = SA (LISTEN,   NO_ACT);
+   aT[LISTEN][SYN_RX]      = SA (LISTEN,   SYN_ACK_TX);//stay in listen and fork
+   aT[LISTEN][SYN_ACK_RX]  = SA (LISTEN,   NO_ACT);
+   aT[LISTEN][FIN_RX]      = SA (LISTEN,   NO_ACT);
+   aT[LISTEN][FIN_ACK_RX]  = SA (LISTEN,   NO_ACT);
+   aT[LISTEN][RST_RX]      = SA (LISTEN,   NO_ACT);
+   aT[LISTEN][BAD_FLAGS]   = SA (LISTEN,   NO_ACT);
+ 
+   // Syn Sent State
+   aT[SYN_SENT][APP_LISTEN]  = SA (CLOSED,      RST_TX);
+   aT[SYN_SENT][APP_CONNECT] = SA (SYN_SENT,    SYN_TX);
+   aT[SYN_SENT][APP_SEND]    = SA (SYN_SENT,    NO_ACT);
+   aT[SYN_SENT][SEQ_RECV]    = SA (ESTABLISHED, NEW_SEQ_RX);
+   aT[SYN_SENT][APP_CLOSE]   = SA (CLOSED,      RST_TX);
+   aT[SYN_SENT][TIMEOUT]     = SA (CLOSED,      NO_ACT);
+   aT[SYN_SENT][ACK_RX]      = SA (SYN_SENT,    NO_ACT);
+   aT[SYN_SENT][SYN_RX]      = SA (SYN_RCVD,    SYN_ACK_TX);
+   aT[SYN_SENT][SYN_ACK_RX]  = SA (ESTABLISHED, ACK_TX_1);
+   aT[SYN_SENT][FIN_RX]      = SA (CLOSED,      RST_TX);
+   aT[SYN_SENT][FIN_ACK_RX]  = SA (CLOSED,      RST_TX);
+   aT[SYN_SENT][RST_RX]      = SA (CLOSED,      APP_NOTIFY);
+   aT[SYN_SENT][BAD_FLAGS]   = SA (CLOSED,      RST_TX);
+ 
+   // Syn Recvd State
+   aT[SYN_RCVD][APP_LISTEN]  = SA (CLOSED,      RST_TX);
+   aT[SYN_RCVD][APP_CONNECT] = SA (CLOSED,      RST_TX);
+   aT[SYN_RCVD][APP_SEND]    = SA (CLOSED,      RST_TX);
+   aT[SYN_RCVD][SEQ_RECV]    = SA (ESTABLISHED, NEW_SEQ_RX);
+   aT[SYN_RCVD][APP_CLOSE]   = SA (FIN_WAIT_1,  FIN_TX);
+   aT[SYN_RCVD][TIMEOUT]     = SA (CLOSED,      RST_TX);
+   aT[SYN_RCVD][ACK_RX]      = SA (ESTABLISHED, SERV_NOTIFY);
+   aT[SYN_RCVD][SYN_RX]      = SA (SYN_RCVD,    SYN_ACK_TX);
+   aT[SYN_RCVD][SYN_ACK_RX]  = SA (CLOSED,      RST_TX);
+   aT[SYN_RCVD][FIN_RX]      = SA (CLOSED,      RST_TX);
+   aT[SYN_RCVD][FIN_ACK_RX]  = SA (CLOSE_WAIT,  PEER_CLOSE);
+   aT[SYN_RCVD][RST_RX]      = SA (CLOSED,      CANCEL_TM);
+   aT[SYN_RCVD][BAD_FLAGS]   = SA (CLOSED,      RST_TX);
+ 
+   // Established State
+   aT[ESTABLISHED][APP_LISTEN] = SA (CLOSED,     RST_TX);
+   aT[ESTABLISHED][APP_CONNECT]= SA (CLOSED,     RST_TX);
+   aT[ESTABLISHED][APP_SEND]   = SA (ESTABLISHED,TX_DATA);
+   aT[ESTABLISHED][SEQ_RECV]   = SA (ESTABLISHED,NEW_SEQ_RX);
+   aT[ESTABLISHED][APP_CLOSE]  = SA (FIN_WAIT_1, FIN_TX);
+   aT[ESTABLISHED][TIMEOUT]    = SA (ESTABLISHED,RETX);
+   aT[ESTABLISHED][ACK_RX]     = SA (ESTABLISHED,NEW_ACK);
+   aT[ESTABLISHED][SYN_RX]     = SA (SYN_RCVD,   SYN_ACK_TX);
+   aT[ESTABLISHED][SYN_ACK_RX] = SA (ESTABLISHED,NO_ACT);
+   aT[ESTABLISHED][FIN_RX]     = SA (CLOSE_WAIT, PEER_CLOSE);
+   aT[ESTABLISHED][FIN_ACK_RX] = SA (CLOSE_WAIT, PEER_CLOSE);
+   aT[ESTABLISHED][RST_RX]     = SA (CLOSED,     CANCEL_TM);
+   aT[ESTABLISHED][BAD_FLAGS]  = SA (CLOSED,     RST_TX);
+ 
+   // Close Wait State
+   aT[CLOSE_WAIT][APP_LISTEN]  = SA (CLOSED,     RST_TX);
+   aT[CLOSE_WAIT][APP_CONNECT] = SA (SYN_SENT,   SYN_TX);
+   aT[CLOSE_WAIT][APP_SEND]    = SA (CLOSE_WAIT, TX_DATA);
+   aT[CLOSE_WAIT][SEQ_RECV]    = SA (CLOSE_WAIT, NEW_SEQ_RX);
+   aT[CLOSE_WAIT][APP_CLOSE]   = SA (LAST_ACK,   FIN_ACK_TX);
+   aT[CLOSE_WAIT][TIMEOUT]     = SA (CLOSE_WAIT, NO_ACT);
+   aT[CLOSE_WAIT][ACK_RX]      = SA (CLOSE_WAIT, NEW_ACK);
+   aT[CLOSE_WAIT][SYN_RX]      = SA (CLOSED,     RST_TX);
+   aT[CLOSE_WAIT][SYN_ACK_RX]  = SA (CLOSED,     RST_TX);
+   aT[CLOSE_WAIT][FIN_RX]      = SA (CLOSE_WAIT, ACK_TX);
+   aT[CLOSE_WAIT][FIN_ACK_RX]  = SA (CLOSE_WAIT, ACK_TX);
+   aT[CLOSE_WAIT][RST_RX]      = SA (CLOSED,     CANCEL_TM);
+   aT[CLOSE_WAIT][BAD_FLAGS]   = SA (CLOSED,     RST_TX);
+ 
+   // Close Last Ack State
+   aT[LAST_ACK][APP_LISTEN]  = SA (CLOSED,      RST_TX);
+   aT[LAST_ACK][APP_CONNECT] = SA (SYN_SENT,    SYN_TX);
+   aT[LAST_ACK][APP_SEND]    = SA (CLOSED,      RST_TX);
+   aT[LAST_ACK][SEQ_RECV]    = SA (LAST_ACK,    NEW_SEQ_RX);
+   aT[LAST_ACK][APP_CLOSE]   = SA (CLOSED,      NO_ACT);
+   aT[LAST_ACK][TIMEOUT]     = SA (CLOSED,      NO_ACT);
+   aT[LAST_ACK][ACK_RX]      = SA (CLOSED,      APP_CLOSED);
+   aT[LAST_ACK][SYN_RX]      = SA (CLOSED,      RST_TX);
+   aT[LAST_ACK][SYN_ACK_RX]  = SA (CLOSED,      RST_TX);
+   aT[LAST_ACK][FIN_RX]      = SA (LAST_ACK,    FIN_ACK_TX);
+   aT[LAST_ACK][FIN_ACK_RX]  = SA (CLOSED,      NO_ACT);
+   aT[LAST_ACK][RST_RX]      = SA (CLOSED,      CANCEL_TM);
+   aT[LAST_ACK][BAD_FLAGS]   = SA (CLOSED,      RST_TX);
+ 
+   // FIN_WAIT_1 state
+   aT[FIN_WAIT_1][APP_LISTEN]  = SA (CLOSED,     RST_TX);
+   aT[FIN_WAIT_1][APP_CONNECT] = SA (CLOSED,     RST_TX);
+   aT[FIN_WAIT_1][APP_SEND]    = SA (CLOSED,     RST_TX);
+   aT[FIN_WAIT_1][SEQ_RECV]    = SA (FIN_WAIT_1, NEW_SEQ_RX);
+   aT[FIN_WAIT_1][APP_CLOSE]   = SA (FIN_WAIT_1, NO_ACT);
+   aT[FIN_WAIT_1][TIMEOUT]     = SA (FIN_WAIT_1, NO_ACT);
+   aT[FIN_WAIT_1][ACK_RX]      = SA (FIN_WAIT_2, NEW_ACK);
+   aT[FIN_WAIT_1][SYN_RX]      = SA (CLOSED,     RST_TX);
+   aT[FIN_WAIT_1][SYN_ACK_RX]  = SA (CLOSED,     RST_TX);
+   aT[FIN_WAIT_1][FIN_RX]      = SA (CLOSING,    ACK_TX);
+   aT[FIN_WAIT_1][FIN_ACK_RX]  = SA (TIME_WAIT, ACK_TX);
+   aT[FIN_WAIT_1][RST_RX]      = SA (CLOSED,     CANCEL_TM);
+   aT[FIN_WAIT_1][BAD_FLAGS]   = SA (CLOSED,     RST_TX);
+ 
+   // FIN_WAIT_2 state
+   aT[FIN_WAIT_2][APP_LISTEN]  = SA (CLOSED,      RST_TX);
+   aT[FIN_WAIT_2][APP_CONNECT] = SA (CLOSED,      RST_TX);
+   aT[FIN_WAIT_2][APP_SEND]    = SA (CLOSED,      RST_TX);
+   aT[FIN_WAIT_2][SEQ_RECV]    = SA (FIN_WAIT_2,  NEW_SEQ_RX);
+   aT[FIN_WAIT_2][APP_CLOSE]   = SA (FIN_WAIT_2,  NO_ACT);
+   aT[FIN_WAIT_2][TIMEOUT]     = SA (FIN_WAIT_2,  NO_ACT);
+   aT[FIN_WAIT_2][ACK_RX]      = SA (FIN_WAIT_2,  NEW_ACK);
+   aT[FIN_WAIT_2][SYN_RX]      = SA (CLOSED,      RST_TX);
+   aT[FIN_WAIT_2][SYN_ACK_RX]  = SA (CLOSED,      RST_TX);
+   aT[FIN_WAIT_2][FIN_RX]      = SA (TIME_WAIT,  ACK_TX);
+   aT[FIN_WAIT_2][FIN_ACK_RX]  = SA (TIME_WAIT,  ACK_TX);
+   aT[FIN_WAIT_2][RST_RX]      = SA (CLOSED,      CANCEL_TM);
+   aT[FIN_WAIT_2][BAD_FLAGS]   = SA (CLOSED,      RST_TX);
+ 
+   // CLOSING state
+   aT[CLOSING][APP_LISTEN]  = SA (CLOSED,      RST_TX);
+   aT[CLOSING][APP_CONNECT] = SA (CLOSED,      RST_TX);
+   aT[CLOSING][APP_SEND]    = SA (CLOSED,      RST_TX);
+   aT[CLOSING][SEQ_RECV]    = SA (CLOSED,      RST_TX);
+   aT[CLOSING][APP_CLOSE]   = SA (CLOSED,      RST_TX);
+   aT[CLOSING][TIMEOUT]     = SA (CLOSING,     NO_ACT);
+   aT[CLOSING][ACK_RX]      = SA (TIME_WAIT,  NO_ACT);
+   aT[CLOSING][SYN_RX]      = SA (CLOSED,      RST_TX);
+   aT[CLOSING][SYN_ACK_RX]  = SA (CLOSED,      RST_TX);
+   aT[CLOSING][FIN_RX]      = SA (CLOSED,      ACK_TX);
+   aT[CLOSING][FIN_ACK_RX]  = SA (CLOSED,      ACK_TX);
+   aT[CLOSING][RST_RX]      = SA (CLOSED,      CANCEL_TM);
+   aT[CLOSING][BAD_FLAGS]   = SA (CLOSED,      RST_TX);
+ 
+   // TIMED_WAIT state
+   aT[TIME_WAIT][APP_LISTEN]  = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][APP_CONNECT] = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][APP_SEND]    = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][SEQ_RECV]    = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][APP_CLOSE]   = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][TIMEOUT]     = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][ACK_RX]      = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][SYN_RX]      = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][SYN_ACK_RX]  = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][FIN_RX]      = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][FIN_ACK_RX]  = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][RST_RX]      = SA (TIME_WAIT, NO_ACT);
+   aT[TIME_WAIT][BAD_FLAGS]   = SA (TIME_WAIT, NO_ACT);
+   // Create the flags lookup table
+   eV[ 0x00] = SEQ_RECV;  // No flags
+   eV[ 0x01] = FIN_RX;    // Fin
+   eV[ 0x02] = SYN_RX;    // Syn
+   eV[ 0x03] = BAD_FLAGS; // Illegal
+   eV[ 0x04] = RST_RX;    // Rst
+   eV[ 0x05] = BAD_FLAGS; // Illegal
+   eV[ 0x06] = BAD_FLAGS; // Illegal
+   eV[ 0x07] = BAD_FLAGS; // Illegal
+   eV[ 0x08] = SEQ_RECV;  // Psh flag is not used
+   eV[ 0x09] = FIN_RX;    // Fin
+   eV[ 0x0a] = SYN_RX;    // Syn
+   eV[ 0x0b] = BAD_FLAGS; // Illegal
+   eV[ 0x0c] = RST_RX;    // Rst
+   eV[ 0x0d] = BAD_FLAGS; // Illegal
+   eV[ 0x0e] = BAD_FLAGS; // Illegal
+   eV[ 0x0f] = BAD_FLAGS; // Illegal
+   eV[ 0x10] = ACK_RX;    // Ack
+   eV[ 0x11] = FIN_ACK_RX;// Fin/Ack
+   eV[ 0x12] = SYN_ACK_RX;// Syn/Ack
+   eV[ 0x13] = BAD_FLAGS; // Illegal
+   eV[ 0x14] = RST_RX;    // Rst
+   eV[ 0x15] = BAD_FLAGS; // Illegal
+   eV[ 0x16] = BAD_FLAGS; // Illegal
+   eV[ 0x17] = BAD_FLAGS; // Illegal
+   eV[ 0x18] = ACK_RX;    // Ack
+   eV[ 0x19] = FIN_ACK_RX;// Fin/Ack
+   eV[ 0x1a] = SYN_ACK_RX;// Syn/Ack
+   eV[ 0x1b] = BAD_FLAGS; // Illegal
+   eV[ 0x1c] = RST_RX;    // Rst
+   eV[ 0x1d] = BAD_FLAGS; // Illegal
+   eV[ 0x1e] = BAD_FLAGS; // Illegal
+   eV[ 0x1f] = BAD_FLAGS; // Illegal
+   eV[ 0x20] = SEQ_RECV;  // No flags (Urgent not presently used)
+   eV[ 0x21] = FIN_RX;    // Fin
+   eV[ 0x22] = SYN_RX;    // Syn
+   eV[ 0x23] = BAD_FLAGS; // Illegal
+   eV[ 0x24] = RST_RX;    // Rst
+   eV[ 0x25] = BAD_FLAGS; // Illegal
+   eV[ 0x26] = BAD_FLAGS; // Illegal
+   eV[ 0x27] = BAD_FLAGS; // Illegal
+   eV[ 0x28] = SEQ_RECV;  // Psh flag is not used
+   eV[ 0x29] = FIN_RX;    // Fin
+   eV[ 0x2a] = SYN_RX;    // Syn
+   eV[ 0x2b] = BAD_FLAGS; // Illegal
+   eV[ 0x2c] = RST_RX;    // Rst
+   eV[ 0x2d] = BAD_FLAGS; // Illegal
+   eV[ 0x2e] = BAD_FLAGS; // Illegal
+   eV[ 0x2f] = BAD_FLAGS; // Illegal
+   eV[ 0x30] = ACK_RX;    // Ack (Urgent not used)
+   eV[ 0x31] = FIN_ACK_RX;// Fin/Ack
+   eV[ 0x32] = SYN_ACK_RX;// Syn/Ack
+   eV[ 0x33] = BAD_FLAGS; // Illegal
+   eV[ 0x34] = RST_RX;    // Rst
+   eV[ 0x35] = BAD_FLAGS; // Illegal
+   eV[ 0x36] = BAD_FLAGS; // Illegal
+   eV[ 0x37] = BAD_FLAGS; // Illegal
+   eV[ 0x38] = ACK_RX;    // Ack
+   eV[ 0x39] = FIN_ACK_RX;// Fin/Ack
+   eV[ 0x3a] = SYN_ACK_RX;// Syn/Ack
+   eV[ 0x3b] = BAD_FLAGS; // Illegal
+   eV[ 0x3c] = RST_RX;    // Rst
+   eV[ 0x3d] = BAD_FLAGS; // Illegal
+   eV[ 0x3e] = BAD_FLAGS; // Illegal
+   eV[ 0x3f] = BAD_FLAGS; // Illegal
+ }
+ 
+ SA TcpStateMachine::Lookup (TcpStates_t s, Events_t e)
+ {
+   NS_LOG_FUNCTION (this << s << e);
+   return aT[s][e];
+ }
+ 
+ Events_t TcpStateMachine::FlagsEvent (uint8_t f)
+ {
+   NS_LOG_FUNCTION (this << f);
+   // Lookup event from flags
+   if (f >= MAX_FLAGS) return BAD_FLAGS;
+   return eV[f]; // Look up flags event
+ }
+ 
+ ////End Pablo (Multipath)
+ 
+ static TcpStateMachine tcpStateMachine; //only instance of a TcpStateMachine
+ 
+ 
+ 
  //TcpL4Protocol stuff----------------------------------------------------------
  
  #undef NS_LOG_APPEND_CONTEXT
diff -crBN old/ns-3.13/src/internet/model/tcp-l4-protocol.h new/ns-3.13/src/internet/model/tcp-l4-protocol.h
*** old/ns-3.13/src/internet/model/tcp-l4-protocol.h	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/model/tcp-l4-protocol.h	2012-11-09 13:01:40.881107000 +0100
***************
*** 114,122 ****
     * This will be used to notify Layer 3 protocol of layer 4 protocol stack to connect them together.
     */
    virtual void NotifyNewAggregate ();
  private:
!   Ptr<Node> m_node;
!   Ipv4EndPointDemux *m_endPoints;
    TypeId m_rttTypeId;
    TypeId m_socketTypeId;
  private:
--- 114,125 ----
     * This will be used to notify Layer 3 protocol of layer 4 protocol stack to connect them together.
     */
    virtual void NotifyNewAggregate ();
+ 
+   Ptr<Node> m_node;                  //Pablo
+   Ipv4EndPointDemux *m_endPoints;   //Pablo
+ 
  private:
! 
    TypeId m_rttTypeId;
    TypeId m_socketTypeId;
  private:
diff -crBN old/ns-3.13/src/internet/model/tcp-typedefs.h new/ns-3.13/src/internet/model/tcp-typedefs.h
*** old/ns-3.13/src/internet/model/tcp-typedefs.h	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/internet/model/tcp-typedefs.h	2012-11-07 09:26:37.013498000 +0100
***************
*** 0 ****
--- 1,105 ----
+ /* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
+ /*
+  * Copyright (c) 2007 Georgia Tech Research Corporation
+  *
+  * This program is free software; you can redistribute it and/or modify
+  * it under the terms of the GNU General Public License version 2 as
+  * published by the Free Software Foundation;
+  *
+  * This program is distributed in the hope that it will be useful,
+  * but WITHOUT ANY WARRANTY; without even the implied warranty of
+  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+  * GNU General Public License for more details.
+  *
+  * You should have received a copy of the GNU General Public License
+  * along with this program; if not, write to the Free Software
+  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
+  *
+  * Author: Raj Bhattacharjea <raj.b@gatech.edu>
+  * typedefs for tcp state machine
+  */ 
+ 
+ #include <vector>
+ #include <map>
+ #include "ns3/address-utils.h"
+ #include "tcp-socket.h"
+ #include "ns3/packet.h"
+ #include "ns3/sequence-number.h"
+ 
+ #ifndef TCP_TYPEDEFS_H
+ #define TCP_TYPEDEFS_H
+ 
+ namespace ns3 {
+ 
+ typedef enum { MAX_FLAGS = 0x40 } TCPMaxFlags_t;  // Flags are 6 bits
+ 
+ 
+ typedef enum {
+   APP_LISTEN,   // 0
+   APP_CONNECT,  // 1
+   APP_SEND,     // 2
+   SEQ_RECV,     // 3
+   APP_CLOSE,    // 4
+   TIMEOUT,      // 5
+   ACK_RX,       // 6
+   SYN_RX,       // 7
+   SYN_ACK_RX,   // 8
+   FIN_RX,       // 9
+   FIN_ACK_RX,   // 10
+   RST_RX,       // 11
+   BAD_FLAGS,    // 12
+   LAST_EVENT } Events_t;
+ 
+ typedef enum {
+   NO_ACT,       // 0
+   ACK_TX,       // 1
+   ACK_TX_1,     // 2 - ACK response to syn
+   RST_TX,       // 3
+   SYN_TX,       // 4
+   SYN_ACK_TX,   // 5
+   FIN_TX,       // 6
+   FIN_ACK_TX,   // 7
+   NEW_ACK,      // 8
+   NEW_SEQ_RX,   // 9
+   RETX,         // 10
+   TX_DATA,      // 11
+   PEER_CLOSE,   // 12
+   APP_CLOSED,   // 13
+   CANCEL_TM,    // 14
+   APP_NOTIFY,   // 15 - Notify app that connection failed
+   SERV_NOTIFY,  // 16 - Notify server tcp that connection completed
+   LAST_ACTION } Actions_t;
+ 
+ class SA  // State/Action pair
+ {
+ public:
+   SA () : state (LAST_STATE), action (LAST_ACTION) { }
+   SA (TcpStates_t s, Actions_t a) : state (s), action (a) { }
+ public:
+   TcpStates_t  state;
+   Actions_t action;
+ };
+ typedef std::vector<SA>  StateActionVec_t;
+ typedef std::vector<StateActionVec_t> StateActions_t;  // One per current state
+ typedef std::vector<Events_t> EventVec_t;      // For flag events lookup
+ 
+ //type for managing buffered out of sequence data
+ 
+ typedef std::map<SequenceNumber32, Ptr<Packet> > UnAckData_t;
+ 
+ 
+ //typedef std::map<SequenceNumber, Ptr<Packet> > UnAckData_t;
+ 
+ class TcpStateMachine {
+   public:
+     TcpStateMachine ();
+     SA Lookup (TcpStates_t, Events_t);
+     Events_t FlagsEvent (uint8_t); // Lookup event from flags
+ 
+   public:
+     StateActions_t aT; // Action table
+     EventVec_t     eV; // Flags event lookup  
+ };
+ 
+ }//namespace ns3
+ #endif //TCP_TYPEDEFS_H
diff -crBN old/ns-3.13/src/internet/model/udp-l4-protocol.cc new/ns-3.13/src/internet/model/udp-l4-protocol.cc
*** old/ns-3.13/src/internet/model/udp-l4-protocol.cc	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/model/udp-l4-protocol.cc	2012-11-07 09:26:37.013498000 +0100
***************
*** 34,43 ****
  #include "ipv4-l3-protocol.h"
  #include "udp-socket-impl.h"
  
! NS_LOG_COMPONENT_DEFINE ("UdpL4Protocol");
  
  namespace ns3 {
  
  NS_OBJECT_ENSURE_REGISTERED (UdpL4Protocol);
  
  /* see http://www.iana.org/assignments/protocol-numbers */
--- 34,44 ----
  #include "ipv4-l3-protocol.h"
  #include "udp-socket-impl.h"
  
! 
  
  namespace ns3 {
  
+ NS_LOG_COMPONENT_DEFINE ("UdpL4Protocol");
  NS_OBJECT_ENSURE_REGISTERED (UdpL4Protocol);
  
  /* see http://www.iana.org/assignments/protocol-numbers */
diff -crBN old/ns-3.13/src/internet/wscript new/ns-3.13/src/internet/wscript
*** old/ns-3.13/src/internet/wscript	2011-12-23 22:09:33.000000000 +0100
--- new/ns-3.13/src/internet/wscript	2012-11-07 09:26:37.013498000 +0100
***************
*** 279,284 ****
--- 279,294 ----
          'helper/ipv6-interface-container.h',
          'helper/ipv6-routing-helper.h',
          'model/ipv6-address-generator.h',
+         'model/tcp-typedefs.h',                          #Pablo Garrido
+         'model/tcp-socket-base.h',                       #Pablo Garrido       
+         'model/tcp-rx-buffer.h',                         #Pablo Garrido
+         'model/tcp-tx-buffer.h',                         #Pablo Garrido       
+         'model/ipv4-end-point-demux.h',                  #Pablo Garrido
+         'model/tcp-socket-factory-impl.h',               #Pablo Garrido
+         'model/ipv4-end-point-demux.h',                  #Pablo Garrido
+         'model/tcp-socket-factory-impl.h',               #Pablo Garrido
+         'model/rtt-estimator.h',                         #Pablo Garrido
+         'model/pending-data.h'                           #Pablo Garrido
         ]
  
      if bld.env['NSC_ENABLED']:
diff -crBN old/ns-3.13/src/mptcp/helper/mp-internet-stack-helper.cc new/ns-3.13/src/mptcp/helper/mp-internet-stack-helper.cc
*** old/ns-3.13/src/mptcp/helper/mp-internet-stack-helper.cc	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/helper/mp-internet-stack-helper.cc	2012-11-09 09:32:26.037106000 +0100
***************
*** 0 ****
--- 1,94 ----
+ #include "ns3/assert.h"
+ #include "ns3/log.h"
+ #include "ns3/object.h"
+ #include "ns3/names.h"
+ #include "ns3/ipv4.h"
+ #include "ns3/ipv6.h"
+ #include "ns3/packet-socket-factory.h"
+ #include "ns3/config.h"
+ #include "ns3/simulator.h"
+ #include "ns3/string.h"
+ #include "ns3/net-device.h"
+ #include "ns3/callback.h"
+ #include "ns3/node.h"
+ #include "ns3/core-config.h"
+ //#include "ns3/pcap-writer.h"
+ //#include "ns3/ascii-writer.h"
+ #include "mp-internet-stack-helper.h"
+ #include "ns3/ipv4-list-routing-helper.h"
+ #include "ns3/ipv4-static-routing-helper.h"
+ #include "ns3/ipv4-global-routing-helper.h"
+ #include "ns3/ipv6-list-routing-helper.h"
+ #include "ns3/ipv6-static-routing-helper.h"
+ #include <limits>
+ 
+ namespace ns3 {
+ 
+ 
+ MpInternetStackHelper::MpInternetStackHelper ()
+   : m_routing (0)
+ {
+   Ipv4StaticRoutingHelper staticRouting;
+   Ipv4GlobalRoutingHelper globalRouting;
+   Ipv4ListRoutingHelper listRouting;
+   Ipv6ListRoutingHelper listRoutingv6;
+   Ipv6StaticRoutingHelper staticRoutingv6;
+   listRouting.Add (staticRouting, 0);
+   listRouting.Add (globalRouting, -10);
+   m_routing = listRouting.Copy ();
+ }
+ 
+ MpInternetStackHelper::~MpInternetStackHelper ()
+ {
+ 
+ }
+ 
+ void
+ MpInternetStackHelper::CreateAndAggregateObjectFromTypeId (Ptr<Node> node, const std::string typeId)
+ {
+   ObjectFactory factory;
+   factory.SetTypeId (typeId);
+   Ptr<Object> protocol = factory.Create <Object> ();
+   node->AggregateObject (protocol);
+ }
+ 
+ void
+ MpInternetStackHelper::Install(NodeContainer nodes)
+ {
+   Ptr<Node> node;
+   ObjectFactory m_tcpFactory;
+   ObjectFactory m_mptcpFactory;
+   m_tcpFactory.SetTypeId ("ns3::TcpL4Protocol");
+   m_mptcpFactory.SetTypeId ("ns3::MpTcpL4Protocol");
+ 
+ 
+   for (NodeContainer::Iterator i = nodes.Begin (); i != nodes.End (); ++i)
+   {
+     node = (*i);
+     if (node->GetObject<Ipv4> () != 0)
+     {
+       NS_FATAL_ERROR ("MpInternetStackHelper::Install (): Aggregating "
+                       "an InternetStack to a node with an existing Ipv4 object");
+       return;
+     }
+     CreateAndAggregateObjectFromTypeId (node, "ns3::ArpL3Protocol");
+     CreateAndAggregateObjectFromTypeId (node, "ns3::Ipv4L3Protocol");
+     //CreateAndAggregateObjectFromTypeId (node, "ns3::MpTcpL4Protocol");
+     CreateAndAggregateObjectFromTypeId (node, "ns3::Icmpv4L4Protocol");
+     CreateAndAggregateObjectFromTypeId (node, "ns3::UdpL4Protocol");
+ 
+     //node->AggregateObject (m_tcpFactory.Create<Object> ());
+     node->AggregateObject (m_mptcpFactory.Create<Object> ());
+     Ptr<PacketSocketFactory> factory = CreateObject<PacketSocketFactory> ();
+     node->AggregateObject (factory);
+ 
+     // Set routing
+     Ptr<Ipv4> ipv4 = node->GetObject<Ipv4> ();
+     Ptr<Ipv4RoutingProtocol> ipv4Routing = m_routing->Create (node);
+     ipv4->SetRoutingProtocol (ipv4Routing);
+ 
+   }
+ }
+ 
+ 
+ } // namespace ns3
diff -crBN old/ns-3.13/src/mptcp/helper/mp-internet-stack-helper.h new/ns-3.13/src/mptcp/helper/mp-internet-stack-helper.h
*** old/ns-3.13/src/mptcp/helper/mp-internet-stack-helper.h	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/helper/mp-internet-stack-helper.h	2012-11-09 09:32:26.037106000 +0100
***************
*** 0 ****
--- 1,39 ----
+ #ifndef MP_INTERNET_STACK_HELPER_H
+ #define MP_INTERNET_STACK_HELPER_H
+ 
+ #include "ns3/node-container.h"
+ #include "ns3/net-device-container.h"
+ #include "ns3/packet.h"
+ #include "ns3/ptr.h"
+ #include "ns3/object-factory.h"
+ //#include "ns3/pcap-writer.h"
+ //#include "ns3/ascii-writer.h"
+ #include "ns3/ipv4-l3-protocol.h"
+ #include "ns3/ipv6-l3-protocol.h"
+ 
+ namespace ns3 {
+ 
+ class Node;
+ class Ipv4RoutingHelper;
+ class Ipv6RoutingHelper;
+ 
+ /**
+  * \brief aggregate IP/TCP/UDP functionality to existing Nodes.
+  */
+ class MpInternetStackHelper
+ {
+ public:
+   MpInternetStackHelper(void);
+   ~MpInternetStackHelper(void);
+   void CreateAndAggregateObjectFromTypeId (Ptr<Node> node, const std::string typeId);
+   void Install(NodeContainer nodes);
+ 
+ 
+ private:
+   Ipv4RoutingHelper *m_routing;
+ 
+ };
+ 
+ } // namespace ns3
+ 
+ #endif /* MP_INTERNET_STACK_HELPER_H */
diff -crBN old/ns-3.13/src/mptcp/model/mp-tcp-header.cc new/ns-3.13/src/mptcp/model/mp-tcp-header.cc
*** old/ns-3.13/src/mptcp/model/mp-tcp-header.cc	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/model/mp-tcp-header.cc	2012-11-28 10:50:08.601095000 +0100
***************
*** 0 ****
--- 1,737 ----
+ #include "mp-tcp-header.h"
+ //#include "ns3/tcp-header"
+ 
+ #include "ns3/address-utils.h"
+ 
+ #include "ns3/log.h"
+ 
+ #include <vector>
+ 
+ 
+ NS_LOG_COMPONENT_DEFINE ("MpTcpHeader");
+ 
+ using namespace std;
+ 
+ namespace ns3 {
+ 
+ NS_OBJECT_ENSURE_REGISTERED (MpTcpHeader);
+ 
+ TypeId
+ MpTcpHeader::GetInstanceTypeId (void) const
+ {
+ 
+   return GetTypeId ();
+ }
+ 
+ void MpTcpHeader::Print (std::ostream &os)
+ {
+   uint8_t flags = GetFlags();
+   os << GetSourcePort() << " > " << GetDestinationPort();
+   if(flags!=0)
+   {
+     os<<" [";
+     if((flags & FIN) != 0)
+     {
+       os<<" FIN ";
+     }
+     if((flags & SYN) != 0)
+     {
+       os<<" SYN ";
+     }
+     if((flags & RST) != 0)
+     {
+       os<<" RST ";
+     }
+     if((flags & PSH) != 0)
+     {
+       os<<" PSH ";
+     }
+     if((flags & ACK) != 0)
+     {
+       os<<" ACK ";
+     }
+     if((flags & URG) != 0)
+     {
+       os<<" URG ";
+     }
+     os<<"]";
+   }
+   os<<" Seq="<< GetSequenceNumber() <<" Ack="<< GetAckNumber() <<" Win="<< GetWindowSize();
+ 
+   //         write options in head
+ 
+   for(uint32_t j=0; j < m_option.size(); j++)
+   {
+       TcpOptions *opt = m_option[j];
+       OptMultipathCapable *optMPC;
+       OptJoinConnection *optJOIN;
+       OptAddAddress *optADDR;
+       OptRemoveAddress *optREMADR;
+       OptDataSeqMapping *optDSN;
+       OptTimesTamp *optTT;
+ 
+       os << opt->optName;
+ 
+       if (opt->optName == OPT_MPC)
+       {
+           optMPC = (OptMultipathCapable *) opt;
+           os << optMPC->senderToken;
+       }else if(opt->optName == OPT_JOIN)
+       {
+           optJOIN = (OptJoinConnection *) opt;
+           os << optJOIN->receiverToken;
+           os << optJOIN->addrID;
+       }else if(opt->optName == OPT_ADDR)
+       {
+           optADDR = (OptAddAddress *) opt;
+           os << optADDR->addrID;
+           optADDR->addr.Print( os );
+       }else if(opt->optName == OPT_REMADR)
+       {
+           optREMADR = (OptRemoveAddress *) opt;
+           os << optREMADR->addrID;
+       }else if(opt->optName == OPT_DSN)
+       {
+           optDSN = (OptDataSeqMapping *) opt;
+           os << optDSN->dataSeqNumber;
+           os << optDSN->dataLevelLength;
+           os << optDSN->subflowSeqNumber;
+       }else if(opt->optName == OPT_TT)
+       {
+           optTT = (OptTimesTamp *) opt;
+           os << optTT->TSval;
+           os << optTT->TSecr;
+       }else if(opt->optName == OPT_DSACK)
+       {
+           OptDSACK* optDSACK = (OptDSACK *) opt;
+           os << optDSACK->blocks[0]; // left Edge  of the first block
+           os << optDSACK->blocks[1]; // right Edge of the first block
+           os << optDSACK->blocks[2]; // left Edge  of the second block
+           os << optDSACK->blocks[3]; // right Edge of the second block
+       }
+   }
+ }
+ 
+ void
+ MpTcpHeader::SetOptionsLength(uint8_t length)
+ {
+     oLen = length;
+ }
+ 
+ vector< TcpOptions* >
+ MpTcpHeader::GetOptions(void) const
+ {
+     return m_option;
+ }
+ 
+ void
+ MpTcpHeader::SetOptions(vector<TcpOptions*> opt)
+ {
+     m_option = opt;
+ }
+ 
+ uint8_t
+ MpTcpHeader::GetOptionsLength() const
+ {
+   /*uint8_t length = 0;
+   TcpOptions *opt;
+ 
+   for(uint32_t j = 0; j < m_option.size(); j++)
+   {
+       opt = m_option[j];
+ 
+       if (opt->optName == OPT_MPC)
+       {
+           length += 5;
+       }else if(opt->optName == OPT_JOIN)
+       {
+           length += 6;
+       }else if(opt->optName == OPT_ADDR)
+       {
+           length += 6;
+       }else if(opt->optName == OPT_REMADR)
+       {
+           length += 2;
+       }else if(opt->optName == OPT_DSN)
+       {
+           length += 15;
+       }
+   }*/
+   return oLen;
+ }
+ 
+ void
+ MpTcpHeader::SetPaddingLength(uint8_t length)
+ {
+     pLen = length;
+ }
+ 
+ uint8_t
+ MpTcpHeader::GetPaddingLength() const
+ {
+     return pLen;
+ }
+ 
+ uint32_t MpTcpHeader::GetSerializedSize (void) const
+ {
+     NS_LOG_FUNCTION_NOARGS();
+   return 4 * GetLength() + GetOptionsLength();
+ }
+ 
+ uint8_t
+ MpTcpHeader::TcpOptionToUint(TcpOption_t opt) const
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     uint8_t i = 0;
+ 
+     if(opt == OPT_MPC)
+         i = 30;
+     else if(opt == OPT_JOIN)
+         i = 31;
+     else if(opt == OPT_ADDR)
+         i = 32;
+     else if(opt == OPT_REMADR)
+         i = 33;
+     else if(opt == OPT_DSN)
+         i = 34;
+     else if(opt == OPT_DSACK)
+         i = 5;
+     else if(opt == OPT_NONE)
+         i = 0;
+     else if(opt == OPT_TT)
+         i = 8; // IANA value is 8
+ 
+     return i;
+ }
+ 
+ TcpOption_t
+ MpTcpHeader::UintToTcpOption(uint8_t kind) const
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     TcpOption_t i = OPT_NONE;
+ 
+     if(kind == 30)
+         i = OPT_MPC;
+     else if(kind == 31)
+         i = OPT_JOIN;
+     else if(kind == 32)
+         i = OPT_ADDR;
+     else if(kind == 33)
+         i = OPT_REMADR;
+     else if(kind == 34)
+         i = OPT_DSN;
+     else if(kind == 5)
+         i = OPT_DSACK;
+     else if(kind == 0)
+         i = OPT_NONE;
+     else if(kind == 8)
+         i = OPT_TT; // IANA value is 8
+ 
+     return i;
+ }
+ 
+ void MpTcpHeader::Serialize (Buffer::Iterator start) const
+ {
+     NS_LOG_FUNCTION(this);
+   Buffer::Iterator i = start;
+   i.WriteHtonU16 (GetSourcePort());
+   i.WriteHtonU16 (GetDestinationPort());
+   i.WriteHtonU32 (GetSequenceNumber().GetValue ()); //Pablo UC
+   i.WriteHtonU32 (GetAckNumber().GetValue ());      //Pablo UC
+   i.WriteHtonU16 ((GetLength() << 12) | GetFlags()); //reserved bits are all zero
+   i.WriteHtonU16 (GetWindowSize());
+   i.WriteHtonU16 (0);
+   i.WriteHtonU16 (GetUrgentPointer());
+ 
+   /*if(m_calcChecksum)
+   {
+     uint16_t headerChecksum = CalculateHeaderChecksum (start.GetSize ());
+     i = start;
+     uint16_t checksum = i.CalculateIpChecksum(start.GetSize (), headerChecksum);
+ 
+     i = start;
+     i.Next(16);
+     i.WriteU16(checksum);
+   } */
+ 
+   //         write options in head
+   for(uint32_t j=0; j < m_option.size(); j++)
+   {
+       TcpOptions *opt = m_option[j];
+       OptMultipathCapable *optMPC;
+       OptJoinConnection *optJOIN;
+       OptAddAddress *optADDR;
+       OptRemoveAddress *optREMADR;
+       OptDataSeqMapping  *optDSN;
+       OptTimesTamp *optTT;
+ NS_LOG_INFO("MpTcpHeader: optName == " << opt->optName);
+       i.WriteU8(TcpOptionToUint (opt->optName));
+ 
+       if (opt->optName == OPT_MPC)
+       {
+           optMPC = (OptMultipathCapable *) opt;
+           i.WriteHtonU32(optMPC->senderToken);
+       }else if(opt->optName == OPT_JOIN)
+       {
+           optJOIN = (OptJoinConnection *) opt;
+           i.WriteHtonU32(optJOIN->receiverToken);
+           i.WriteU8(optJOIN->addrID);
+       }else if(opt->optName == OPT_ADDR)
+       {
+           optADDR = (OptAddAddress *) opt;
+           i.WriteU8(optADDR->addrID);
+           i.WriteHtonU32(optADDR->addr.Get());
+       }else if(opt->optName == OPT_REMADR)
+       {
+           optREMADR = (OptRemoveAddress *) opt;
+           i.WriteU8(optREMADR->addrID);
+       }else if(opt->optName == OPT_DSN)
+       {
+           optDSN = (OptDataSeqMapping *) opt;
+           i.WriteU64(optDSN->dataSeqNumber);
+           i.WriteHtonU16(optDSN->dataLevelLength);
+           i.WriteHtonU32(optDSN->subflowSeqNumber);
+       }else if(opt->optName == OPT_TT) // Option TCP TimesTamp
+       {
+           optTT = (OptTimesTamp *) opt;
+           i.WriteU64(optTT->TSval);
+           i.WriteU64(optTT->TSecr);
+       }else if(opt->optName == OPT_DSACK) // Option Duplicate SACK
+       {
+           OptDSACK *dsak = (OptDSACK *) opt;
+           i.WriteU64(dsak->blocks[0]);  // left Edge  of the first block
+           i.WriteU64(dsak->blocks[1]);  // right Edge  of the first block
+           i.WriteU64(dsak->blocks[2]);  // left Edge  of the second block
+           i.WriteU64(dsak->blocks[3]);  // right Edge  of the second block
+           NS_LOG_LOGIC("Serialize -> fstLeft ("<< dsak->blocks[0] <<") fstRight ("<< dsak->blocks[1] <<") sndLeft ("<< dsak->blocks[2] <<") sndRight ("<< dsak->blocks[3] <<")");
+       }
+   }
+   for(int j = 0; j < (int)pLen; j++)
+       i.WriteU8(255);
+ NS_LOG_INFO("MpTcpHeader::Serialize options length  olen = " << (int)oLen);
+ NS_LOG_INFO("MpTcpHeader::Serialize padding length  plen = " << (int)pLen);
+ }
+ 
+ uint32_t MpTcpHeader::Deserialize (Buffer::Iterator start)
+ {
+     NS_LOG_FUNCTION(this);
+     uint8_t hlen = 0;
+     uint8_t plen = 0;
+   Buffer::Iterator i = start;
+   SetSourcePort (i.ReadNtohU16 ());
+   SetDestinationPort (i.ReadNtohU16 ());
+   //m_sequenceNumber = i.ReadNtohU32 ();
+   //m_ackNumber = i.ReadNtohU32 ();
+   SetSequenceNumber (SequenceNumber32(i.ReadNtohU32 ()));
+   SetAckNumber (SequenceNumber32(i.ReadNtohU32 ()));
+   uint16_t field = i.ReadNtohU16 ();
+   SetFlags (field & 0x3F);
+   hlen = (field>>12);
+   SetLength (hlen);
+   SetWindowSize (i.ReadNtohU16 ());
+   i.Next (2);
+   SetUrgentPointer (i.ReadNtohU16 ());
+ 
+   hlen = (hlen - 5) * 4;
+ 
+   /*if(m_calcChecksum)
+     {
+       uint16_t headerChecksum = CalculateHeaderChecksum (start.GetSize ());
+       i = start;
+       uint16_t checksum = i.CalculateIpChecksum(start.GetSize (), headerChecksum);
+       m_goodChecksum = (checksum == 0);
+     }*/
+ 
+   // handle options field
+ NS_LOG_INFO("MpTcpHeader::Deserialize looking for options");
+   while( ! i.IsEnd() && hlen > 0)
+   {
+       TcpOptions *opt;
+ 
+       TcpOption_t kind = (TcpOption_t) i.ReadU8();
+ NS_LOG_INFO("MpTcpHeader::Deserialize options found: " << kind << ", hlen = " << (int)hlen);
+       if (kind == OPT_MPC)
+       {
+           opt = new OptMultipathCapable (kind, i.ReadNtohU32());
+           plen = (plen + 5) % 4;
+           hlen -= 5;
+       }else if(kind == OPT_JOIN)
+       {
+           opt = new OptJoinConnection (kind, i.ReadNtohU32(), i.ReadU8());
+           plen = (plen + 6) % 4;
+           hlen -= 6;
+       }else if(kind == OPT_ADDR)
+       {
+           opt = new OptAddAddress (kind, i.ReadU8(), Ipv4Address(i.ReadNtohU32()));
+           plen = (plen + 6) % 4;
+           hlen -= 6;
+       }else if(kind == OPT_REMADR)
+       {
+           opt = new OptRemoveAddress (kind, i.ReadU8());
+           plen = (plen + 2) % 4;
+           hlen -= 2;
+       }else if(kind == OPT_DSN)
+       {
+           opt = new OptDataSeqMapping (kind, i.ReadU64(), i.ReadNtohU16(), i.ReadNtohU32());
+           plen = (plen + 15) % 4;
+           hlen -= 15;
+       }else if(kind == OPT_TT)
+       {
+           opt = new OptTimesTamp (kind, i.ReadU64(), i.ReadU64());
+           plen = (plen + 17) % 4;
+           hlen -= 17;
+       }else if(kind == OPT_DSACK)
+       {
+           OptDSACK *dsak = new OptDSACK(kind);
+           uint64_t fstLeft = i.ReadU64(), fstRight = i.ReadU64();
+           uint64_t sndLeft = i.ReadU64(), sndRight = i.ReadU64();
+           dsak->AddfstBlock(fstLeft, fstRight);
+           dsak->AddBlock(sndLeft, sndRight);
+           NS_LOG_LOGIC("Deserialize -> fstLeft ("<< dsak->blocks[0] <<") fstRight ("<< dsak->blocks[1] <<") sndLeft ("<< dsak->blocks[2] <<") sndRight ("<< dsak->blocks[3] <<")");
+           opt = dsak;
+           plen = (plen + 33) % 4;
+           hlen -= 33;
+       }else
+       {
+           // the rest are pending octets, so leave
+           hlen = 0;
+           break;
+       }
+ 
+       m_option.insert(m_option.end(), opt);
+ 
+   }
+   i.Next (plen);
+   NS_LOG_INFO("MpTcpHeader::Deserialize leaving this method");
+ 
+   return GetSerializedSize ();
+ }
+ 
+ TcpOptions::TcpOptions(void)
+     : optName (OPT_NONE)
+ {
+     //NS_LOG_FUNCTION_NOARGS();
+ }
+ 
+ TcpOptions::~TcpOptions(void)
+ {
+     //NS_LOG_FUNCTION_NOARGS();
+     optName = OPT_NONE;
+ }
+ 
+ OptMultipathCapable::OptMultipathCapable(TcpOption_t oName, uint32_t TxToken)
+ {
+     NS_LOG_FUNCTION(this << oName << TxToken);
+     optName     = oName;
+     Length      = 5; // field "length" is not insert in the packet
+     senderToken = TxToken;
+ }
+ 
+ OptMultipathCapable::~OptMultipathCapable()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     optName     = OPT_NONE;
+     Length      = 0; // field "length" is not insert in the packet
+     senderToken = 0;
+ }
+ 
+ OptJoinConnection::OptJoinConnection(TcpOption_t oName, uint32_t RxToken, uint8_t aID)
+ {
+     NS_LOG_FUNCTION(this << oName << RxToken << aID);
+     optName       = oName;
+     Length        = 6;
+     receiverToken = RxToken;
+     addrID        = aID;
+ }
+ 
+ OptJoinConnection::~OptJoinConnection()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     optName       = OPT_NONE;
+     Length        = 0;
+     receiverToken = 0;
+     addrID        = 0;
+ }
+ 
+ OptAddAddress::OptAddAddress(TcpOption_t oName, uint8_t aID, Ipv4Address address)
+ {
+     NS_LOG_FUNCTION(this << oName << aID << address);
+     optName  = oName;
+     Length   = 6;
+     addrID   = aID;
+     addr     = address;
+ }
+ 
+ OptAddAddress::~OptAddAddress()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     optName  = OPT_NONE;
+     Length   = 0;
+     addrID   = 0;
+     addr     = Ipv4Address::GetZero();
+ }
+ 
+ OptRemoveAddress::OptRemoveAddress(TcpOption_t oName, uint8_t aID)
+ {
+     NS_LOG_FUNCTION(this << oName << aID);
+     optName  = oName;
+     Length   = 5;
+     addrID   = aID;
+ }
+ 
+ OptRemoveAddress::~OptRemoveAddress()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     optName  = OPT_NONE;
+     Length   = 0;
+     addrID   = 0;
+ }
+ 
+ OptDataSeqMapping::OptDataSeqMapping(TcpOption_t oName, uint64_t dSeqNum, uint16_t dLevelLength, uint32_t sfSeqNum)
+ {
+     NS_LOG_FUNCTION(this << oName << dSeqNum << dLevelLength << sfSeqNum);
+     optName  = oName;
+     Length      = 11;
+     dataSeqNumber   = dSeqNum;
+     dataLevelLength = dLevelLength;
+     subflowSeqNumber = sfSeqNum;
+ }
+ 
+ OptDataSeqMapping::~OptDataSeqMapping()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     optName  = OPT_NONE;
+     Length      = 0;
+     dataSeqNumber  = 0;
+     dataLevelLength = 0;
+     subflowSeqNumber = 0;
+ }
+ 
+ OptTimesTamp::OptTimesTamp(TcpOption_t oName, uint64_t tsval, uint64_t tsecr)
+ {
+     NS_LOG_FUNCTION(this << oName << tsval << tsecr);
+     optName = oName;
+     Length  = 17;
+     TSval   = tsval;
+     TSecr   = tsecr;
+ }
+ 
+ OptTimesTamp::~OptTimesTamp()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     optName  = OPT_NONE;
+     TSval    = 0;
+     TSecr    = 0;
+ }
+ 
+ OptDSACK::OptDSACK(TcpOption_t oName)
+   : blocks (0)
+ {
+     optName = oName;
+ }
+ 
+ void
+ OptDSACK::AddBlock (uint64_t leftEdge, uint64_t rightEdge)
+ {
+     blocks.insert (blocks.end(), leftEdge);
+     blocks.insert (blocks.end(), rightEdge);
+ }
+ 
+ void
+ OptDSACK::AddfstBlock (uint64_t leftEdge, uint64_t rightEdge)
+ {
+     // we first insert the right edge in the begining then the left edge to keep the order
+     blocks.insert (blocks.begin(), rightEdge);
+     blocks.insert (blocks.begin(), leftEdge);
+ }
+ 
+ OptDSACK::~OptDSACK()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     blocks.clear ();
+ }
+ 
+ TypeId
+ MpTcpHeader::GetTypeId (void)
+ {
+     static TypeId tid = TypeId("ns3::MpTcpHeader")
+                     .SetParent<TcpHeader>()
+                     .AddConstructor<MpTcpHeader> ()
+                     ;
+     return tid;
+ }
+ 
+ MpTcpHeader::MpTcpHeader ()
+   : m_option (0), oLen (0), pLen(0), original (true)
+ {
+     NS_LOG_FUNCTION_NOARGS();
+ }
+ 
+ MpTcpHeader::MpTcpHeader (const MpTcpHeader &res)
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     SetSourcePort      ( res.GetSourcePort () );
+     SetDestinationPort ( res.GetDestinationPort () );
+     SetFlags           ( res.GetFlags () );
+     SetSequenceNumber  ( res.GetSequenceNumber () );
+     SetAckNumber       ( res.GetAckNumber () );
+     SetWindowSize      ( res.GetWindowSize () );
+     //SetOptions         ( res.GetOptions () );
+     SetLength          ( res.GetLength () );
+     SetOptionsLength   ( res.GetOptionsLength () );
+     SetPaddingLength   ( res.GetPaddingLength () );
+     SetOptions         ( res.GetOptions () );
+     original           = false;
+ }
+ 
+ MpTcpHeader
+ MpTcpHeader::Copy ()
+ {
+     MpTcpHeader l4Header;
+     NS_LOG_FUNCTION_NOARGS();
+     l4Header.SetSourcePort      ( GetSourcePort () );
+     l4Header.SetDestinationPort ( GetDestinationPort () );
+     l4Header.SetFlags           ( GetFlags () );
+     l4Header.SetSequenceNumber  ( GetSequenceNumber () );
+     l4Header.SetAckNumber       ( GetAckNumber () );
+     l4Header.SetWindowSize      ( GetWindowSize () );
+     l4Header.SetOptions         ( GetOptions () );
+     l4Header.SetLength          ( GetLength () );
+     l4Header.SetOptionsLength   ( GetOptionsLength () );
+     l4Header.SetPaddingLength   ( GetPaddingLength () );
+     return l4Header;
+ }
+ 
+ MpTcpHeader::~MpTcpHeader ()
+ {
+     if ( original == false )
+         return;
+     NS_LOG_FUNCTION_NOARGS();
+     for(uint32_t i=0; i < m_option.size() ; i++)
+     {
+         if ( m_option[i] != 0 )
+         switch( m_option[i]->optName )
+         {
+             case OPT_MPC:
+                 delete (OptMultipathCapable*) m_option[i];
+                 break;
+             case OPT_JOIN:
+                 delete (OptJoinConnection*) m_option[i];
+                 break;
+             case OPT_ADDR:
+                 delete (OptAddAddress*) m_option[i];
+                 break;
+             case OPT_REMADR:
+                 delete (OptRemoveAddress*) m_option[i];
+                 break;
+             case OPT_DSN:
+                 delete (OptDataSeqMapping*) m_option[i];
+                 break;
+             case OPT_TT:
+                 delete (OptTimesTamp*) m_option[i];
+                 break;
+             default:
+                 break;
+         }
+     }
+     m_option.clear();
+     oLen = 0;
+ }
+ 
+ bool
+ MpTcpHeader::AddOptMPC(TcpOption_t optName, uint32_t TxToken)
+ {
+     NS_LOG_FUNCTION(this);
+     if (optName == OPT_MPC)
+     {
+         OptMultipathCapable* opt = new OptMultipathCapable(optName, TxToken);
+ 
+         m_option.insert(m_option.end(), opt);
+ 
+         return true;
+     }
+     return false;
+ }
+ 
+ bool
+ MpTcpHeader::AddOptJOIN(TcpOption_t optName, uint32_t RxToken, uint8_t addrID)
+ {
+     NS_LOG_FUNCTION(this);
+     if (optName == OPT_JOIN)
+     {
+         OptJoinConnection* opt = new OptJoinConnection(optName, RxToken, addrID);
+ 
+         m_option.insert(m_option.end(), opt);
+         return true;
+     }
+     return false;
+ }
+ 
+ bool
+ MpTcpHeader::AddOptADDR(TcpOption_t optName, uint8_t addrID, Ipv4Address addr)
+ {
+     NS_LOG_FUNCTION(this);
+     if (optName == OPT_ADDR)
+     {
+         OptAddAddress* opt = new OptAddAddress(optName, addrID, addr);
+ 
+         m_option.insert(m_option.end(), opt);
+         return true;
+     }
+     return false;
+ }
+ 
+ bool
+ MpTcpHeader::AddOptREMADR(TcpOption_t optName, uint8_t addrID)
+ {
+     NS_LOG_FUNCTION(this);
+     if (optName == OPT_REMADR)
+     {
+         OptRemoveAddress* opt = new OptRemoveAddress(optName, addrID);
+ 
+         m_option.insert(m_option.end(), opt);
+         return true;
+     }
+     return false;
+ }
+ 
+ bool
+ MpTcpHeader::AddOptDSN(TcpOption_t optName, uint64_t dSeqNum, uint16_t dLevelLength, uint32_t sfSeqNum)
+ {
+     NS_LOG_FUNCTION(this);
+     if (optName == OPT_DSN)
+     {
+         OptDataSeqMapping* opt = new OptDataSeqMapping(optName, dSeqNum, dLevelLength, sfSeqNum);
+ 
+         m_option.insert(m_option.end(), opt);
+         return true;
+     }
+     return false;
+ }
+ 
+ bool
+ MpTcpHeader::AddOptTT(TcpOption_t optName, uint64_t tsval, uint64_t tsecr)
+ {
+     NS_LOG_FUNCTION(this);
+     if (optName == OPT_TT)
+     {
+         OptTimesTamp* opt = new OptTimesTamp(optName, tsval, tsecr);
+ 
+         m_option.insert(m_option.end(), opt);
+         return true;
+     }
+     return false;
+ }
+ 
+ bool
+ MpTcpHeader::AddOptDSACK(TcpOption_t optName, OptDSACK *ptrDSAK)
+ {
+     NS_LOG_FUNCTION(this);
+     if (optName == OPT_DSACK)
+     {
+         m_option.insert(m_option.end(), ptrDSAK);
+         return true;
+     }
+     return false;
+ }
+ }
diff -crBN old/ns-3.13/src/mptcp/model/mp-tcp-header.h new/ns-3.13/src/mptcp/model/mp-tcp-header.h
*** old/ns-3.13/src/mptcp/model/mp-tcp-header.h	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/model/mp-tcp-header.h	2012-11-16 12:35:21.549661000 +0100
***************
*** 0 ****
--- 1,162 ----
+ #ifndef MP_TCP_HEADER_H
+ #define MP_TCP_HEADER_H
+ 
+ #include <stdint.h>
+ #include <string>
+ #include "ns3/header.h"
+ #include "ns3/tcp-header.h"
+ #include "ns3/ipv4-address.h"
+ 
+ #include <vector>
+ 
+ 
+ using namespace std;
+ 
+ 
+ namespace ns3 {
+ 
+ typedef enum {
+     OPT_NONE   = 0,
+     OPT_DSACK  = 5,
+     OPT_TT     = 8,      // Times Tamp
+     OPT_MPC    = 30,
+     OPT_JOIN   = 31,
+     OPT_ADDR   = 32,
+     OPT_REMADR = 33,
+     OPT_DSN    = 34
+     } TcpOption_t;
+ 
+ class TcpOptions
+ {
+ public:
+     TcpOptions();
+     virtual ~TcpOptions();
+ 
+     TcpOption_t optName;
+     uint8_t Length;
+ };
+ 
+ class OptMultipathCapable : public TcpOptions
+ {
+ public:
+     virtual ~OptMultipathCapable();
+     uint32_t senderToken;
+     OptMultipathCapable(TcpOption_t oName, uint32_t TxToken);
+ };
+ 
+ class OptJoinConnection : public TcpOptions
+ {
+ public:
+     virtual ~OptJoinConnection();
+     uint32_t receiverToken;
+     uint8_t addrID;
+     OptJoinConnection(TcpOption_t oName, uint32_t RxToken, uint8_t aID);
+ };
+ 
+ class OptAddAddress : public TcpOptions
+ {
+ public:
+     virtual ~OptAddAddress();
+     uint8_t addrID;
+     Ipv4Address addr;
+     OptAddAddress(TcpOption_t oName, uint8_t aID, Ipv4Address address);
+ };
+ 
+ class OptRemoveAddress : public TcpOptions
+ {
+ public:
+     virtual ~OptRemoveAddress();
+     uint8_t addrID;
+     OptRemoveAddress(TcpOption_t oName, uint8_t aID);
+ };
+ 
+ class OptDataSeqMapping : public TcpOptions
+ {
+ public:
+     virtual ~OptDataSeqMapping();
+     uint64_t dataSeqNumber;
+     uint16_t dataLevelLength;
+     uint32_t subflowSeqNumber;
+     OptDataSeqMapping(TcpOption_t oName, uint64_t dSeqNum, uint16_t dLevelLength, uint32_t sfSeqNum);
+ };
+ 
+ class OptTimesTamp : public TcpOptions
+ {
+ public:
+     virtual ~OptTimesTamp();
+     uint64_t TSval;     // TS Value      in milliseconds
+     uint64_t TSecr;     // TS Echo Reply in milliseconds
+ 
+     OptTimesTamp(TcpOption_t oName, uint64_t tsval, uint64_t tsecr);
+ };
+ 
+ /*! \brief Implémentation de l'option DSACK (Duplicate SACK) adaptée à MPTCP.
+  *
+  *
+  *
+  */
+ class OptDSACK : public TcpOptions
+ {
+ public:
+     virtual ~OptDSACK();
+     vector<uint64_t> blocks;     // a vector of 4-bytes fields, representing the DSACK block's edge
+          // the size of the vector is a multiple of 2 (a block has to limits, upper and lower) representing the length of the table
+ 
+     OptDSACK (TcpOption_t oName);
+     void AddBlock (uint64_t leftEdge, uint64_t rightEdge);
+     void AddfstBlock (uint64_t leftEdge, uint64_t rightEdge);
+ };
+ 
+ class MpTcpHeader : public TcpHeader
+ {
+ public:
+   static TypeId  GetTypeId (void);
+ 
+   MpTcpHeader (void);
+   MpTcpHeader (const MpTcpHeader &res);
+   ~MpTcpHeader (void);
+ 
+   MpTcpHeader Copy ();
+ 
+   // Multipath capable Option
+   bool AddOptMPC(TcpOption_t optName, uint32_t TxToken);
+   // Join Connection Option
+   bool AddOptJOIN(TcpOption_t optName, uint32_t RxToken, uint8_t addrID);
+   // Add address Option
+   bool AddOptADDR(TcpOption_t optName, uint8_t addrID, Ipv4Address addr);
+   // Remove address Option
+   bool AddOptREMADR(TcpOption_t optName, uint8_t addrID);
+   // Data Sequence Mapping Option
+   bool AddOptDSN(TcpOption_t optName, uint64_t dSeqNum, uint16_t dLevelLength, uint32_t sfSeqNum);
+   // TCP TimesTamp Option
+   bool AddOptTT(TcpOption_t optName, uint64_t tsval, uint64_t tsecr);
+   // DSACK Option
+   bool AddOptDSACK(TcpOption_t optName, OptDSACK *opt);
+ 
+   virtual TypeId GetInstanceTypeId (void) const;
+   virtual void Print (std::ostream &os);
+   virtual uint32_t GetSerializedSize (void) const;
+   virtual void Serialize (Buffer::Iterator start) const;
+   virtual uint32_t Deserialize (Buffer::Iterator start);
+ 
+   void SetOptionsLength(uint8_t length);
+   void SetPaddingLength(uint8_t length);
+   uint8_t GetOptionsLength() const;
+   uint8_t GetPaddingLength() const;
+   uint8_t TcpOptionToUint(TcpOption_t opt) const;
+   TcpOption_t UintToTcpOption(uint8_t kind) const;
+ 
+   vector< TcpOptions* > GetOptions(void) const;
+   void SetOptions (vector<TcpOptions*> opt);
+ 
+ protected:
+   vector< TcpOptions* > m_option;
+   uint8_t oLen;
+   uint8_t pLen;
+   bool original;
+ 
+ };
+ 
+ } // namespace ns3
+ 
+ #endif /* MP_TCP_HEADER */
diff -crBN old/ns-3.13/src/mptcp/model/mp-tcp-l4-protocol.cc new/ns-3.13/src/mptcp/model/mp-tcp-l4-protocol.cc
*** old/ns-3.13/src/mptcp/model/mp-tcp-l4-protocol.cc	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/model/mp-tcp-l4-protocol.cc	2012-12-18 10:26:46.902359000 +0100
***************
*** 0 ****
--- 1,280 ----
+ #include "ns3/assert.h"
+ #include "ns3/log.h"
+ #include "ns3/nstime.h"
+ #include "ns3/boolean.h"
+ #include "ns3/object-vector.h"
+ 
+ #include "ns3/packet.h"
+ #include "ns3/node.h"
+ #include "ns3/ipv4-route.h"
+ 
+ #include "mp-tcp-l4-protocol.h"
+ #include "ns3/tcp-header.h"
+ #include "ns3/ipv4-end-point-demux.h"
+ #include "ns3/ipv4-end-point.h"
+ #include "ns3/ipv4-l3-protocol.h"
+ #include "ns3/tcp-socket-factory-impl.h"
+ #include "ns3/tcp-socket-base.h"
+ #include "ns3/rtt-estimator.h"
+ #include "ns3/tcp-typedefs.h"
+ #include "ns3/ipv4-header.h"
+ 
+ #include <vector>
+ #include <list>
+ #include <sstream>
+ #include <iomanip>
+ 
+ NS_LOG_COMPONENT_DEFINE ("MpTcpL4Protocol");
+ 
+ namespace ns3 {
+ 
+ NS_OBJECT_ENSURE_REGISTERED (MpTcpL4Protocol);
+ 
+ const uint8_t MpTcpL4Protocol::PROT_NUMBER = 6;
+ 
+ 
+ TypeId
+ MpTcpL4Protocol::GetTypeId (void)
+ {
+   static TypeId tid = TypeId ("ns3::MpTcpL4Protocol")
+     .SetParent<TcpL4Protocol> ()
+     .AddConstructor<MpTcpL4Protocol> ()
+     ;
+   return tid;
+ }
+ 
+ MpTcpL4Protocol::MpTcpL4Protocol ()
+ //  : m_endPoints (new Ipv4EndPointDemux ())
+ {
+   NS_LOG_FUNCTION_NOARGS ();
+   NS_LOG_LOGIC("Made a MpTcpL4Protocol "<<this);
+   m_endPoints = new Ipv4EndPointDemux ();
+ }
+ 
+ MpTcpL4Protocol::~MpTcpL4Protocol ()
+ {
+   NS_LOG_FUNCTION_NOARGS ();
+ }
+ int
+ MpTcpL4Protocol::GetProtocolNumber (void) const
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+   return PROT_NUMBER;
+ }
+ 
+ void
+ MpTcpL4Protocol::NotifyNewAggregate ()
+ {
+     NS_LOG_FUNCTION (this);
+   if (m_node == 0)
+     {
+       Ptr<Node> node = this->GetObject<Node> ();
+       if (node != 0)
+         {
+          Ptr<Ipv4L3Protocol> ipv4 = this->GetObject<Ipv4L3Protocol> ();
+     	 //Ptr<Ipv4> ipv4 = this->GetObject<Ipv4> ();   //Pablo
+           if (ipv4 != 0)
+             {
+               this->SetNode (node);
+               ipv4->Insert (this);
+               Ptr<TcpSocketFactoryImpl> tcpFactory = CreateObject<TcpSocketFactoryImpl> ();
+               tcpFactory->SetTcp (this);
+               node->AggregateObject (tcpFactory);
+             }
+         }
+     }
+   Object::NotifyNewAggregate ();
+ }
+ 
+ 
+ enum Ipv4L4Protocol::RxStatus
+ MpTcpL4Protocol::Receive (Ptr<Packet> packet, Ipv4Header const &ipHeader, Ptr<Ipv4Interface> incomingInterface)
+ {
+ 	NS_LOG_FUNCTION_NOARGS();
+   //NS_LOG_FUNCTION (this << packet << source << destination << incomingInterface);
+   MpTcpHeader mptcpHeader;
+ 
+   Ipv4Address source=ipHeader.GetSource();            //Pablo UC
+   Ipv4Address destination=ipHeader.GetDestination();      //Pablo UC
+ 
+ 
+   /*if(Node::ChecksumEnabled ())
+   {
+     mptcpHeader.EnableChecksums();
+     mptcpHeader.InitializeChecksum (source, destination, PROT_NUMBER);
+   }
+ */
+   packet->PeekHeader (mptcpHeader);
+   uint16_t srcPort = mptcpHeader.GetSourcePort ();
+   uint16_t dstPort = mptcpHeader.GetDestinationPort ();
+  // uint32_t seq=mptcpHeader.GetSequenceNumber();
+ //  NS_LOG_UNCOND("Source: "<< source<<" Port: "<< srcPort << " Destination: "<< destination << " dstPort"<< dstPort);
+   NS_LOG_LOGIC("MpTcpL4Protocol " << this << " receiving seq " << mptcpHeader.GetSequenceNumber() << " ack " << mptcpHeader.GetAckNumber() << " flags "<< std::hex << (int)mptcpHeader.GetFlags() << std::dec << " data size " << packet->GetSize());
+ 
+ /*
+   if(!tcpHeader.IsChecksumOk ())
+   {
+     NS_LOG_INFO("Bad checksum, dropping packet!");
+     return Ipv4L4Protocol::RX_CSUM_FAILED;
+   }
+ */
+ 
+   ////Pablo UC// CALL TO TRACE
+ 
+   if (!m_mpTraceCallback.IsNull())
+ 	  m_mpTraceCallback (packet,ipHeader);
+   ////Pablo UC
+ 
+ 
+   NS_LOG_LOGIC ("MpTcpL4Protocol "<<this<<" received a packet");
+   Ipv4EndPointDemux::EndPoints endPoints = m_endPoints->Lookup (destination, dstPort, source, srcPort,incomingInterface);
+   if (endPoints.empty ())
+   {
+       // trying with destination port
+       NS_LOG_LOGIC ("MpTcpL4Protocol:Receive() ->  Trying to look up for end point with destination port: "<< dstPort);
+       Ipv4EndPointDemux::EndPoints allEndPoints = m_endPoints->GetAllEndPoints();
+       Ipv4EndPointDemux::EndPoints::iterator it;
+       while( allEndPoints.size() > 0)
+       {
+           it = allEndPoints.begin();
+           uint16_t localPort = (*it)->GetLocalPort ();
+           if(localPort != dstPort)
+           {
+             it = allEndPoints.erase(it);
+           }
+           else
+           {
+             NS_LOG_LOGIC ("MpTcpL4Protocol:Receive() ->  related end port for destination port ("<< dstPort << ") is found");
+             break;
+           }
+       }
+       (*allEndPoints.begin ())->SetLocalAddress ( destination );
+       (*allEndPoints.begin ())->SetPeer (source, srcPort);
+       (*allEndPoints.begin ())->ForwardUp (packet, ipHeader, srcPort, incomingInterface); //change
+ NS_LOG_INFO ("MpTcpL4Protocol (endPoint is empty) forwarding up to endpoint/socket dest = " << destination<<" dstPort "<<dstPort<<" src = " << source);
+ 
+       NS_LOG_INFO ("MpTcpL4Protocol -> leaving Receive");
+       return Ipv4L4Protocol::RX_OK;
+   }
+ 
+   if (endPoints.empty ())
+   {
+     NS_LOG_LOGIC ("  No endpoints matched on MpTcpL4Protocol "<<this);
+     std::ostringstream oss;
+     oss<<"  destination IP: ";
+     destination.Print (oss);
+     oss<<" destination port: "<< dstPort <<" source IP: ";
+     source.Print (oss);
+     oss<<" source port: "<< srcPort;
+     NS_LOG_LOGIC (oss.str ());
+ /*
+     if (!(tcpHeader.GetFlags () & TcpHeader::RST))
+       {
+         // build a RST packet and send
+         Ptr<Packet> rstPacket = Create<Packet> ();
+         TcpHeader header;
+         if (tcpHeader.GetFlags () & TcpHeader::ACK)
+           {
+             // ACK bit was set
+             header.SetFlags (TcpHeader::RST);
+             header.SetSequenceNumber (header.GetAckNumber ());
+           }
+         else
+           {
+             header.SetFlags (TcpHeader::RST | TcpHeader::ACK);
+             header.SetSequenceNumber (SequenceNumber (0));
+             header.SetAckNumber (header.GetSequenceNumber () + SequenceNumber (1));
+           }
+         header.SetSourcePort (tcpHeader.GetDestinationPort ());
+         header.SetDestinationPort (tcpHeader.GetSourcePort ());
+         SendPacket (rstPacket, header, destination, source);
+         return Ipv4L4Protocol::RX_ENDPOINT_CLOSED;
+       }
+     else
+       {
+         return Ipv4L4Protocol::RX_ENDPOINT_CLOSED;
+       }
+ */
+   }
+ 
+   NS_ASSERT_MSG (endPoints.size() == 1 , "Demux returned more than one endpoint");
+ NS_LOG_INFO ("MpTcpL4Protocol (endPoint not empty) forwarding up to endpoint/socket dest = " << destination<<" dstPort "<<dstPort<<" src = " << source);
+ 
+   (*endPoints.begin ())->SetLocalAddress ( destination );
+   (*endPoints.begin ())->SetPeer (source, srcPort);
+ 
+ 
+ 
+   (*endPoints.begin ())->ForwardUp (packet, ipHeader, srcPort,incomingInterface);
+ 
+   return Ipv4L4Protocol::RX_OK;
+ 
+ }
+ 
+ void
+ MpTcpL4Protocol::DoDispose(void)
+ {
+   NS_LOG_FUNCTION_NOARGS ();
+   /*for (std::vector<Ptr<TcpSocketImpl> >::iterator i = m_sockets.begin (); i != m_sockets.end (); i++)
+     {
+       *i = 0;
+     }
+   m_sockets.clear ();
+ */
+   if (m_endPoints != 0)
+     {
+       delete m_endPoints;
+       m_endPoints = 0;
+     }
+ 
+   m_node = 0;
+   Ipv4L4Protocol::DoDispose ();
+ }
+ 
+ void
+ MpTcpL4Protocol::SendPacket (Ptr<Packet> p, MpTcpHeader l4Header, Ipv4Address src, Ipv4Address dst)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     NS_LOG_LOGIC("MpTcpL4Protocol " << this ); /*
+               << " sending seq " << l4Header.GetSequenceNumber()
+               << " ack " << l4Header.GetAckNumber()
+               << " flags " << std::hex << (int)header.GetFlags() << std::dec
+               << " data size " << p->GetSize());*/
+     NS_LOG_FUNCTION (this << p << src << dst);
+     //Ptr<MpTcpHeader> ptrHeader = CopyObject<MpTcpHeader>(l4Header);
+     p->AddHeader (l4Header);
+ NS_LOG_INFO ("MpTcpL4Protocol::SendPacket -> header added successfully !");
+     Ptr<Ipv4L3Protocol> ipv4 = m_node->GetObject<Ipv4L3Protocol> ();
+     if (ipv4 != 0)
+     {
+       // XXX We've already performed the route lookup in TcpSocketImpl
+       // should be cached.
+       Ipv4Header l3Header;
+       l3Header.SetDestination (dst);
+       Socket::SocketErrno errno_;
+       Ptr<Ipv4Route> route;
+       //uint32_t oif = 0; //specify non-zero if bound to a source address
+       Ptr<NetDevice> oif (0);
+       // use oif to specify the interface output (see Ipv4RoutingProtocol class)
+       route = ipv4->GetRoutingProtocol ()->RouteOutput (p, l3Header, oif, errno_);
+       NS_LOG_INFO ("MpTcpL4Protocol::SendPacket -> packet size: " << p->GetSize() <<" sAddr " << src<<" dstAddr " << dst);
+       NS_LOG_INFO ("MpTcpL4Protocol::SendPacket -> Protocol n°:" << (int)PROT_NUMBER);
+       NS_LOG_INFO ("MpTcpL4Protocol::SendPacket -> route      :" << route);
+       ipv4->Send (p, src, dst, PROT_NUMBER, route);
+       NS_LOG_INFO ("MpTcpL4Protocol::SendPacket -> leaving !");
+     }
+     else
+       NS_FATAL_ERROR("Trying to use MpTcp on a node without an Ipv4 interface");
+ 
+ }
+ ////Pablo UC
+ void
+ MpTcpL4Protocol::SetMpTraceCallback(MpTraceCallback callback)
+ {
+ 	m_mpTraceCallback = callback;
+ }
+ ////End Pablo UC
+ 
+ }; // namespace ns3
+ 
+ 
diff -crBN old/ns-3.13/src/mptcp/model/mp-tcp-l4-protocol.h new/ns-3.13/src/mptcp/model/mp-tcp-l4-protocol.h
*** old/ns-3.13/src/mptcp/model/mp-tcp-l4-protocol.h	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/model/mp-tcp-l4-protocol.h	2012-11-23 12:49:30.385797000 +0100
***************
*** 0 ****
--- 1,62 ----
+ #ifndef MP_TCP_L4_PROTOCOL_H
+ #define MP_TCP_L4_PROTOCOL_H
+ 
+ 
+ 
+ #include <stdint.h>
+ #include <vector>
+ 
+ 
+ #include "ns3/packet.h"
+ #include "ns3/ipv4-address.h"
+ #include "ns3/ptr.h"
+ #include "ns3/object-factory.h"
+ #include "ns3/ipv4-l4-protocol.h"
+ #include "ns3/tcp-l4-protocol.h"
+ #include "ns3/tcp-typedefs.h"
+ #include "ns3/ipv4-end-point-demux.h"
+ #include "mp-tcp-header.h"
+ #include "mp-tcp-socket-base.h"
+ 
+ 
+ namespace ns3 {
+ 
+ class MpTcpL4Protocol : public TcpL4Protocol {
+ 
+ public:
+ 
+   /////Pablo UC////////
+   typedef Callback<void,Ptr<Packet>, Ipv4Header> MpTraceCallback;
+   ///End Pablo UC////////
+ 
+   static const uint8_t PROT_NUMBER;
+   static TypeId GetTypeId (void);
+ 
+   MpTcpL4Protocol ();
+   virtual ~MpTcpL4Protocol ();
+ 
+   virtual int GetProtocolNumber (void) const;
+   virtual enum Ipv4L4Protocol::RxStatus Receive (Ptr<Packet> packet, Ipv4Header const &ipHeader, Ptr<Ipv4Interface> incomingInterface);
+   void SendPacket (Ptr<Packet> p, MpTcpHeader l4Header, Ipv4Address src, Ipv4Address dst);
+ 
+   ////Pablo UC //
+   void SetMpTraceCallback(MpTraceCallback callback);
+   ////End Pablo UC ///
+ 
+ protected:
+   virtual void DoDispose (void);
+ 
+   virtual void NotifyNewAggregate ();
+ 
+   //std::vector<Ptr<MpTcpSocketImpl> > m_sockets;
+ 
+   //Pablo UC/////////
+ private:
+   MpTraceCallback m_mpTraceCallback;
+   //End Pablo UC////
+ };
+ 
+ }; // namespace ns3
+ 
+ 
+ #endif /* MP_TCP_L4_PROTOCOL_H */
diff -crBN old/ns-3.13/src/mptcp/model/mp-tcp-socket-base.cc new/ns-3.13/src/mptcp/model/mp-tcp-socket-base.cc
*** old/ns-3.13/src/mptcp/model/mp-tcp-socket-base.cc	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/model/mp-tcp-socket-base.cc	2012-12-18 10:53:15.413212000 +0100
***************
*** 0 ****
--- 1,2899 ----
+ /* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
+ /*
+  * Copyright (c) 2010 Adrian Sai-wah Tam
+  *
+  * This program is free software; you can redistribute it and/or modify
+  * it under the terms of the GNU General Public License version 2 as
+  * published by the Free Software Foundation;
+  *
+  * This program is distributed in the hope that it will be useful,
+  * but WITHOUT ANY WARRANTY; without even the implied warranty of
+  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+  * GNU General Public License for more details.
+  *
+  * You should have received a copy of the GNU General Public License
+  * along with this program; if not, write to the Free Software
+  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
+  *
+  * Author: Adrian Sai-wah Tam <adrian.sw.tam@gmail.com>
+  */
+ 
+ #define NS_LOG_APPEND_CONTEXT \
+   if (m_node) { std::clog << Simulator::Now ().GetSeconds () << " [node " << m_node->GetId () << "] "; }
+ 
+ #include "mp-tcp-socket-base.h"
+ 
+ 
+ #include "ns3/abort.h"
+ #include "ns3/node.h"
+ #include "ns3/inet-socket-address.h"
+ #include "ns3/log.h"
+ #include "ns3/ipv4.h"
+ #include "ns3/ipv4-interface-address.h"
+ #include "ns3/ipv4-route.h"
+ #include "ns3/ipv4-interface.h"
+ #include "ns3/ipv4-routing-protocol.h"
+ #include "ns3/simulation-singleton.h"
+ #include "ns3/simulator.h"
+ #include "ns3/packet.h"
+ #include "ns3/uinteger.h"
+ #include "ns3/trace-source-accessor.h"
+ #include "ns3/string.h"
+ #include "ns3/tcp-typedefs.h"
+ #include "ns3/ipv4-end-point.h"
+ #include "ns3/tcp-header.h"
+ #include "ns3/rtt-estimator.h"
+ #include "ns3/ipv4-l3-protocol.h"
+ #include "ns3/gnuplot.h"
+ #include "ns3/error-model.h"
+ #include "time.h"
+ #include "ns3/point-to-point-channel.h"
+ #include "ns3/point-to-point-net-device.h"
+ #include "mp-tcp-typedefs.h"
+ #include "ns3/tcp-socket-base.h"
+ #include "mp-tcp-l4-protocol.h"
+ //#include "nstime.h"
+ 
+ #include <vector>
+ #include <map>
+ #include <algorithm>
+ #include <stdlib.h>
+ 
+ #include <iostream>
+ #include <fstream>
+ 
+ NS_LOG_COMPONENT_DEFINE ("MpTcpSocketBase");
+ 
+ using namespace std;
+ 
+ namespace ns3 {
+ 
+ 
+ NS_OBJECT_ENSURE_REGISTERED (MpTcpSocketBase);
+ 
+ //TypeId
+ //MpTcpSocketBase::GetTypeId (void)
+ //{
+ //  static TypeId tid = TypeId ("ns3::MpTcpSocketBase")
+ //    .SetParent<TcpSocketBase> ()
+ //    .AddConstructor<MpTcpSocketBase> ()
+ //    .AddAttribute ("ReTxThreshold", "Threshold for fast retransmit",
+ //                    UintegerValue (3),
+ //                    MakeUintegerAccessor (&MpTcpSocketBase::m_retxThresh),
+ //                    MakeUintegerChecker<uint32_t> ())
+ //    .AddTraceSource ("CongestionWindow",
+ //                     "The TCP connection's congestion window",
+ //                     MakeTraceSourceAccessor (&MpTcpSocketBase::m_cWnd))
+ //  ;
+ //  return tid;
+ //}
+ 
+ TypeId
+ MpTcpSocketBase::GetTypeId (void)
+ {
+ 	 static TypeId tid = TypeId("ns3::MpTcpSocketBase")
+ 			 .SetParent<TcpSocketBase> ()
+ 			 .AddConstructor<MpTcpSocketBase> ()
+ 	 ;
+ 	 return tid;
+ }
+ 
+ //MpTcpSocketBase::MpTcpSocketBase (void) : m_retxThresh (3), m_inFastRec (false)
+ //{
+ //  NS_LOG_FUNCTION (this);
+ //}
+ 
+ MpTcpSocketBase::MpTcpSocketBase (void)
+ {
+ 
+ 	NS_LOG_FUNCTION(this);
+ 	    //srand (time(NULL));
+ 	    srand (65536);
+ 	    m_state        = CLOSED;
+ 	    m_node         = 0;
+ 	    m_connected    = false;
+ 	    m_stateMachine = new MpTcpStateMachine();
+ 
+ 	    // multipath variable
+ 	    m_maxSubFlowNumber = 255;
+ 	    m_minSubFlowNumber = 1;
+ 	    m_subFlowNumber = 0;
+ 	    m_mpState     = MP_NONE;
+ 	    m_mpSendState = MP_NONE;
+ 	    m_mpRecvState = MP_NONE;
+ 	    m_mpEnabled   = false;
+ 	    m_addrAdvertised = false;
+ 	    m_localToken  = 0;
+ 	    m_remoteToken = 0;
+ 	    m_aggregatedBandwidth = 0;
+ 	    m_lastUsedsFlowIdx = 0;
+ 
+ 	    totalCwnd = 0;
+ 	    meanTotalCwnd = 0;
+ 
+ 	    // flow control
+ 	    m_rxBufSize  = 0;
+ 	    m_lastRxAck  = 0;
+ 
+ 	    m_skipRetxResched = false;
+ 	    m_dupAckCount  = 0;
+ 	    m_delAckCount  = 0;
+ 
+ 	    nextTxSequence   = 1;
+ 	    nextRxSequence   = 1;
+ 	    remoteRecvWnd    = 1;
+ 	    unAckedDataCount = 0;
+ 
+ 	    m_algoCC = RTT_Compensator;
+ 	    m_distribAlgo = Round_Robin;
+ 	    m_algoPR = NoPR_Algo;
+ 
+ 	    nbRejected = 0;
+ 	    nbReceived = 0;
+ 	    unOrdMaxSize  = 0;
+ 
+ 	    client = false;
+ 	    server = false;
+ 
+ 	    lastRetransmit = 0;
+ 	    frtoStep = Step_1;
+ 	    useFastRecovery = false;
+ }
+ 
+ //MpTcpSocketBase::MpTcpSocketBase (const MpTcpSocketBase& sock)
+ //  : TcpSocketBase (sock),
+ //    m_cWnd (sock.m_cWnd),
+ //    m_ssThresh (sock.m_ssThresh),
+ //    m_initialCWnd (sock.m_initialCWnd),
+ //    m_retxThresh (sock.m_retxThresh),
+ //    m_inFastRec (false)
+ //{
+ //  NS_LOG_FUNCTION (this);
+ //  NS_LOG_LOGIC ("Invoked the copy constructor");
+ //}
+ 
+ MpTcpSocketBase::MpTcpSocketBase (Ptr<Node> node)
+ 	: subflows (0), localAddrs (0), remoteAddrs (0)
+   {
+     NS_LOG_FUNCTION (node->GetId() << this);
+ 	//srand (time(NULL));
+ 	srand (65536);
+ 	m_state        = CLOSED;
+ 	m_node         = node;
+ 	m_connected    = false;
+ 	m_stateMachine = new MpTcpStateMachine();
+ 	m_mptcp = node->GetObject<MpTcpL4Protocol> ();
+ 	NS_ASSERT_MSG(m_mptcp != 0, "node->GetObject<MpTcpL4Protocol> () returned NULL");
+ 
+ 	// multipath variable
+ 	m_maxSubFlowNumber = 255;
+ 	m_minSubFlowNumber = 1;
+ 	m_subFlowNumber    = 0;
+ 	m_mpState = MP_NONE;
+ 	m_mpSendState = MP_NONE;
+ 	m_mpRecvState = MP_NONE;
+ 	m_mpEnabled = false;
+ 	m_addrAdvertised = false;
+ 	m_localToken = 0;
+ 	m_remoteToken = 0;
+ 	m_aggregatedBandwidth = 0;
+ 	m_lastUsedsFlowIdx = 0;
+ 
+ 	totalCwnd = 0;
+ 	meanTotalCwnd = 0;
+ 
+     nextTxSequence   = 1;
+     nextRxSequence   = 1;
+ 
+ 	m_skipRetxResched = false;
+ 	m_dupAckCount = 0;
+ 	m_delAckCount = 0;
+ 
+ 	// flow control
+ 	m_rxBufSize = 0;
+ 	m_lastRxAck = 0;
+     congestionWnd = 1;
+ 
+ 	remoteRecvWnd    = 1;
+ 	unAckedDataCount = 0;
+ 
+ 	m_algoCC = RTT_Compensator;
+ 	m_distribAlgo = Round_Robin;
+ 	m_algoPR = NoPR_Algo;
+ 
+ 	nbRejected = 0;
+ 	nbReceived = 0;
+ 	unOrdMaxSize  = 0;
+ 
+ 	client = false;
+ 	server = false;
+ 
+ 	lastRetransmit = 0;
+ 	frtoStep = Step_1;
+ 	useFastRecovery = false;
+ }
+ 
+ 
+ 
+ //MpTcpSocketBase::~MpTcpSocketBase (void)
+ //{
+ //}
+ 
+ MpTcpSocketBase::~MpTcpSocketBase (void)
+ {
+   NS_LOG_FUNCTION (m_node->GetId() << this);
+   m_state        = CLOSED;
+   m_node         = 0;
+   m_mptcp        = 0;
+   m_connected    = false;
+   delete m_stateMachine;
+   delete m_pendingData;
+   //subflows.clear();
+   for(int i = 0; i < (int) localAddrs.size(); i ++)
+     delete localAddrs[i];
+   localAddrs.clear();
+   for(int i = 0; i < (int) remoteAddrs.size(); i ++)
+     delete remoteAddrs[i];
+   remoteAddrs.clear();
+   delete sendingBuffer;
+   delete recvingBuffer;
+ }
+ 
+ //CHANGE
+ 
+ uint8_t
+ MpTcpSocketBase::GetMaxSubFlowNumber ()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     return m_maxSubFlowNumber;
+ }
+ 
+ void
+ MpTcpSocketBase::SetMaxSubFlowNumber (uint8_t num)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     m_maxSubFlowNumber = num;
+ }
+ 
+ uint8_t
+ MpTcpSocketBase::GetMinSubFlowNumber ()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     return m_minSubFlowNumber;
+ }
+ 
+ void
+ MpTcpSocketBase::SetMinSubFlowNumber (uint8_t num)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     m_minSubFlowNumber = num;
+ }
+ 
+ bool
+ MpTcpSocketBase::SetLossThreshold(uint8_t sFlowIdx, double lossThreshold)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     if(sFlowIdx >= subflows.size())
+         return false;
+     subflows[sFlowIdx]->LostThreshold = lossThreshold;
+     return true;
+ }
+ 
+ void
+ MpTcpSocketBase::SetPacketReorderAlgo (PacketReorder_t pralgo)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     m_algoPR = pralgo;
+ }
+ 
+ 
+ Ptr<MpTcpSocketBase>
+ MpTcpSocketBase::Copy ()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+   return CopyObject<MpTcpSocketBase> (this);
+ }
+ 
+ void
+ MpTcpSocketBase::SetNode (Ptr<Node> node)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     m_node = node;
+ }
+ 
+ Ptr<Node>
+ MpTcpSocketBase::GetNode ()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     return m_node;
+ }
+ 
+ void
+ MpTcpSocketBase::SetMpTcp (Ptr<MpTcpL4Protocol> mptcp)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     m_mptcp = mptcp;
+ }
+ 
+ uint32_t
+ MpTcpSocketBase::getL3MTU (Ipv4Address addr)
+ {
+ 	NS_LOG_FUNCTION_NOARGS() ;
+ 
+     // return the MTU associated to the layer 3
+     Ptr<Ipv4L3Protocol> l3Protocol = m_node->GetObject<Ipv4L3Protocol> ();
+     return l3Protocol->GetMtu ( l3Protocol->GetInterfaceForAddress (addr) )-100;
+ }
+ 
+ uint64_t
+ MpTcpSocketBase::getBandwidth (Ipv4Address addr)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     uint64_t bd = 0;
+     StringValue uiv;
+     std::string name = std::string("DataRate");
+     Ptr<Ipv4L3Protocol> l3Protocol = m_node->GetObject<Ipv4L3Protocol> ();
+     Ptr<Ipv4Interface> ipv4If = l3Protocol->GetInterface (l3Protocol->GetInterfaceForAddress (addr));
+     Ptr< NetDevice > netDevice = ipv4If->GetDevice();
+     // if the device is a point to point one, then the data rate can be retrived directly from the device
+     // if it's a CSMA one, then you should look at the corresponding channel
+     if( netDevice->IsPointToPoint () == true )
+     {
+         netDevice->GetAttribute(name, (AttributeValue &) uiv);
+         // converting the StringValue to a string, then deleting the 'bps' end
+         std::string str = uiv.SerializeToString(0);
+         std::istringstream iss( str.erase(str.size() - 3) );
+         iss >> bd;
+     }
+     return bd;
+ }
+ 
+ //CHANGE
+ 
+ 
+ 
+ /** We initialize m_cWnd from this function, after attributes initialized */
+ 
+ //int
+ //MpTcpSocketBase::Listen (void)
+ //{
+ //  NS_LOG_FUNCTION (this);
+ //  InitializeCwnd ();
+ //  return TcpSocketBase::Listen ();
+ //}
+ 
+ int
+ MpTcpSocketBase::Listen (void)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     //NS_LOG_FUNCTION_NOARGS();
+     // detect all interfaces on which the node can receive a SYN packet
+ 
+     MpTcpSubFlow *sFlow = new MpTcpSubFlow();
+     sFlow->routeId = (subflows.size() == 0 ? 0:subflows[subflows.size() - 1]->routeId + 1);
+     sFlow->sAddr   = m_endPoint->GetLocalAddress ();
+     sFlow->sPort   = m_endPoint->GetLocalPort ();
+     m_localPort    = m_endPoint->GetLocalPort ();
+     sFlow->MSS     = getL3MTU (m_endPoint->GetLocalAddress ());
+     sFlow->bandwidth = getBandwidth (m_endPoint->GetLocalAddress ());
+     subflows.insert (subflows.end(), sFlow);
+     if(m_state != CLOSED)
+     {
+         m_errno = ERROR_INVAL;
+         return -1;
+     }
+     // aT[CLOSED][APP_LISTEN] = SA(LISTEN, NO_ACT)
+     // used as a reference when creating subsequent subflows
+     m_state = LISTEN;
+ 
+     ProcessAction(subflows.size() - 1 , ProcessEvent(subflows.size() - 1, APP_LISTEN));
+     return 0;
+ }
+ 
+ /** We initialize m_cWnd from this function, after attributes initialized */
+ //int
+ //MpTcpSocketBase::Connect (const Address & address)
+ //{
+ //  NS_LOG_FUNCTION (this << address);
+ //  InitializeCwnd ();
+ //  return TcpSocketBase::Connect (address);
+ //}
+ 
+ int
+ MpTcpSocketBase::Connect (Ipv4Address servAddr, uint16_t servPort)
+ {
+     NS_LOG_FUNCTION (m_node->GetId()<< this << servAddr << servPort );
+     MpTcpSubFlow *sFlow = new MpTcpSubFlow();
+     sFlow->routeId  = (subflows.size() == 0 ? 0:subflows[subflows.size() - 1]->routeId + 1);
+     sFlow->dAddr    = servAddr;
+     sFlow->dPort    = servPort;
+     m_remoteAddress = servAddr;
+     m_remotePort    = servPort;
+     Ptr<Ipv4> ipv4  = m_node->GetObject<Ipv4> ();
+     if (m_endPoint == 0)
+     {// no end point allocated for this socket => try to allocate a new one
+         if (Bind() == -1)
+         {
+             NS_ASSERT (m_endPoint == 0);
+             return -1;
+         }
+         NS_ASSERT (m_endPoint != 0);
+     }
+     // check if whether the node have a routing protocol
+     sFlow->sAddr = m_endPoint->GetLocalAddress ();
+     sFlow->sPort = m_endPoint->GetLocalPort ();
+     sFlow->MSS   = getL3MTU(m_endPoint->GetLocalAddress ());
+     sFlow->bandwidth = getBandwidth(m_endPoint->GetLocalAddress ());
+     subflows.insert(subflows.end(), sFlow);
+ 
+     if(ipv4->GetRoutingProtocol() == 0)
+     {
+         NS_FATAL_ERROR("No Ipv4RoutingProtocol in the node");
+     }
+     else
+     {
+         Ipv4Header header;
+         header.SetDestination (servAddr);
+         Socket::SocketErrno errno_;
+         Ptr<Ipv4Route> route;
+         Ptr<NetDevice> oif (0);
+         //uint32_t oif = 0;
+         route = ipv4->GetRoutingProtocol ()->RouteOutput(Ptr<Packet> (), header, oif, errno_);
+         if (route != 0)
+         {
+             NS_LOG_LOGIC("Route existe");
+             m_endPoint->SetLocalAddress (route->GetSource ());
+         }
+         else
+         {
+             NS_LOG_LOGIC ("MpTcpSocketBase"<<m_node->GetId()<<"::Connect():  Route to " << m_remoteAddress << " does not exist");
+             NS_LOG_ERROR (errno_);
+             m_errno = errno_;
+             return -1;
+         }
+     }
+     // Sending SYN packet
+     bool success = ProcessAction (subflows.size() - 1, ProcessEvent (subflows.size() - 1,APP_CONNECT) );
+     if ( !success )
+     {
+         return -1;
+     }
+   return 0;
+ }
+ 
+ 
+ int
+ MpTcpSocketBase::Connect (Address &address)
+ {
+     NS_LOG_FUNCTION ( this << address );
+ 
+     // convert the address (Address => InetSocketAddress)
+     InetSocketAddress transport = InetSocketAddress::ConvertFrom (address);
+     m_remoteAddress = transport.GetIpv4();
+     m_remotePort    = transport.GetPort();
+     return Connect(m_remoteAddress, m_remotePort);
+ }
+ 
+ 
+ //Fast recovery and fast retransmit
+ void
+ MpTcpSocketBase::DupAck (const TcpHeader& t, uint32_t count)
+ {
+   NS_LOG_FUNCTION (this << "t " << count);
+  if (count == m_retxThresh && !m_inFastRec)
+     { // triple duplicate ack triggers fast retransmit (RFC2581, sec.3.2)
+       m_ssThresh = std::max (2 * m_segmentSize, BytesInFlight () / 2);
+       m_cWnd = m_ssThresh + 3 * m_segmentSize;
+       m_inFastRec = true;
+       NS_LOG_INFO ("Triple dupack. Reset cwnd to " << m_cWnd << ", ssthresh to " << m_ssThresh);
+       DoRetransmit ();
+     }
+   else if (m_inFastRec)
+     { // In fast recovery, inc cwnd for every additional dupack (RFC2581, sec.3.2)
+       m_cWnd += m_segmentSize;
+       NS_LOG_INFO ("Increased cwnd to " << m_cWnd);
+       SendPendingData ();
+     };
+ }
+ 
+ 
+ //Change
+ 
+ int
+ MpTcpSocketBase::Bind ()
+ {
+     //Allocate an endPoint for this socket
+     NS_LOG_FUNCTION_NOARGS ();
+     client = true;
+     m_endPoint = m_mptcp->Allocate();
+     return Binding();
+ }
+ 
+ 
+ int
+ MpTcpSocketBase::Binding (void)
+ {
+     NS_LOG_FUNCTION_NOARGS ();
+     if (m_endPoint == 0)
+     {
+         return -1;
+     }
+     // set the call backs method
+ 
+ 
+     m_endPoint->SetRxCallback (MakeCallback (&MpTcpSocketBase::ForwardUp, Ptr<MpTcpSocketBase>(this)));
+     m_endPoint->SetDestroyCallback (MakeCallback (&MpTcpSocketBase::Destroy, Ptr<MpTcpSocketBase>(this)));
+ 
+     // set the local parameters
+     m_localAddress = m_endPoint->GetLocalAddress();
+     m_localPort    = m_endPoint->GetLocalPort();
+     return 0;
+ }
+ 
+ int
+ MpTcpSocketBase::Bind (const Address &address)
+ {
+   NS_LOG_FUNCTION (m_node->GetId()<<":"<<this<<address);
+   server = true;
+   if (!InetSocketAddress::IsMatchingType (address))
+     {
+       m_errno = ERROR_INVAL;
+       return -1;
+     }
+   else
+       NS_LOG_DEBUG("MpTcpSocketBase:Bind: Address ( " << address << " ) is valid");
+   InetSocketAddress transport = InetSocketAddress::ConvertFrom (address);
+   Ipv4Address ipv4 = transport.GetIpv4 ();
+   uint16_t port = transport.GetPort ();
+   NS_LOG_LOGIC("MpTcpSocketBase:Bind: Ipv4Address: "<< ipv4 << ", Port: " << port);
+ 
+   if (ipv4 == Ipv4Address::GetAny () && port == 0)
+     {
+       m_endPoint = m_mptcp->Allocate ();
+       NS_LOG_LOGIC ("MpTcpSocketBase "<<this<<" got an endpoint: "<<m_endPoint);
+     }
+   else if (ipv4 == Ipv4Address::GetAny () && port != 0)
+     {
+       m_endPoint = m_mptcp->Allocate (port);
+       NS_LOG_LOGIC ("MpTcpSocketBase "<<this<<" got an endpoint: "<<m_endPoint);
+     }
+   else if (ipv4 != Ipv4Address::GetAny () && port == 0)
+     {
+       m_endPoint = m_mptcp->Allocate (ipv4);
+       NS_LOG_LOGIC ("MpTcpSocketBase "<<this<<" got an endpoint: "<<m_endPoint);
+     }
+   else if (ipv4 != Ipv4Address::GetAny () && port != 0)
+     {
+       m_endPoint = m_mptcp->Allocate (ipv4, port);
+       NS_LOG_LOGIC ("MpTcpSocketBase "<<this<<" got an endpoint: "<<m_endPoint);
+     }else
+         NS_LOG_DEBUG("MpTcpSocketBase:Bind(@): unable to allocate an end point !");
+ 
+   return Binding ();
+ }
+ 
+ bool
+ MpTcpSocketBase::SendBufferedData ()
+ {
+   NS_LOG_FUNCTION("SendBufferdData"<< Simulator::Now ().GetSeconds () );
+   uint8_t sFlowIdx = m_lastUsedsFlowIdx; // i prefer getSubflowToUse (), but this one gives the next one
+   Ptr<Ipv4L3Protocol> ipv4 = m_node->GetObject<Ipv4L3Protocol> ();
+ 
+   if ( !ProcessAction (sFlowIdx, ProcessEvent (sFlowIdx, APP_SEND) ))
+   {
+       return false; // Failed, return zero
+   }
+   return true;
+ }
+ 
+ int
+ MpTcpSocketBase::FillBuffer (uint8_t* buf, uint32_t size)
+ {
+   NS_LOG_FUNCTION( this << size );
+   return sendingBuffer->Add(buf, size);
+ }
+ 
+ bool
+ MpTcpSocketBase::SendPendingData ()
+ {
+     NS_LOG_INFO("====================================================================================");
+   NS_LOG_FUNCTION_NOARGS ();
+   uint32_t nOctetsSent = 0;
+ 
+   MpTcpSubFlow *sFlow;
+ 
+   while ( ! sendingBuffer->Empty() )
+   {
+         uint8_t count   = 0;
+         uint32_t window = 0;
+         while ( count < subflows.size() )
+         {
+             count ++;
+             window = std::min (AvailableWindow (m_lastUsedsFlowIdx), sendingBuffer->PendingData()); // Get available window size
+             if( window == 0 )
+             {
+                 // No more available window in the current subflow, try with another one
+                 m_lastUsedsFlowIdx = getSubflowToUse ();
+             }
+             else
+             {
+                 NS_LOG_LOGIC ("MpTcpSocketBase::SendPendingData -> PendingData (" << sendingBuffer->PendingData() << ") Available window ("<<AvailableWindow (m_lastUsedsFlowIdx)<<")");
+                 break;
+             }
+         }
+         if ( count == subflows.size() && window == 0 )
+         {
+             // No available window for transmission in all subflows, abort sending
+             break;
+         }
+ 
+       sFlow = subflows[m_lastUsedsFlowIdx];
+       if(sFlow->state == ESTABLISHED)
+       {
+         Ipv4Address sAddr   = sFlow->sAddr;
+         Ipv4Address dAddr   = sFlow->dAddr;
+         uint16_t sPort      = sFlow->sPort;
+         uint16_t dPort      = sFlow->dPort;
+         uint32_t mss        = sFlow->MSS;
+         uint8_t hlen = 5;
+         uint8_t olen = 15 ;
+         uint8_t plen = 0;
+ 
+         uint32_t size = std::min (window, mss);  // Send no more than window
+         Ptr<Packet> pkt = sendingBuffer->CreatePacket(size);
+         if(pkt == 0)
+             break;
+ 
+         NS_LOG_LOGIC ("MpTcpSocketBase SendPendingData on subflow " << (int)m_lastUsedsFlowIdx << " w " << window << " rxwin " << AdvertisedWindowSize () << " CWND "  << sFlow->cwnd << " segsize " << sFlow->MSS << " nextTxSeq " << nextTxSequence << " nextRxSeq " << nextRxSequence << " pktSize " << size);
+         uint8_t  flags   = TcpHeader::ACK;
+ 
+         MpTcpHeader header;
+         header.SetSourcePort      (sPort);
+         header.SetDestinationPort (dPort);
+         header.SetFlags           (flags);
+         header.SetSequenceNumber  (SequenceNumber32(sFlow->TxSeqNumber));
+       //header.SetSequenceNumber  (sFlow->TxSeqNumber);
+         uint32_t temp=sFlow->RxSeqNumber;
+         header.SetAckNumber       (SequenceNumber32(temp));
+         header.SetWindowSize      (AdvertisedWindowSize());
+       // save the seq number of the sent data
+         sFlow->AddDSNMapping      (m_lastUsedsFlowIdx, nextTxSequence, size, sFlow->TxSeqNumber, sFlow->RxSeqNumber, pkt->Copy() );
+         header.AddOptDSN          (OPT_DSN, nextTxSequence, size, sFlow->TxSeqNumber);
+ 
+         switch ( m_algoPR )
+         {
+             case Eifel:
+                 header.AddOptTT   (OPT_TT, Simulator::Now ().GetMilliSeconds (), 0);
+                 olen += 17;
+                 break;
+             default:
+                 break;
+         }
+ 
+         plen = (4 - (olen % 4)) % 4;
+         olen = (olen + plen) / 4;
+         hlen += olen;
+         header.SetLength(hlen);
+         header.SetOptionsLength(olen);
+         header.SetPaddingLength(plen);
+ 
+         SetReTxTimeout (m_lastUsedsFlowIdx);
+ 
+         // simulating loss of acknowledgement in the sender side
+         calculateTotalCWND ();
+ 
+ 
+           if( sFlow->LostThreshold > 0.0 && sFlow->LostThreshold < 1.0 )
+           {
+               //Ptr<RateErrorModel> eModel = CreateObjectWithAttributes<RateErrorModel> ("RanVar", RandomVariableValue (UniformVariable (0., 1.)), "ErrorRate", DoubleValue (sFlow->LostThreshold));
+               //if ( ! eModel->IsCorrupt (pkt) )
+               if ( rejectPacket(sFlow->LostThreshold) == false )
+               {
+                  m_mptcp->SendPacket (pkt, header, sAddr, dAddr);
+               }else
+               {
+                   NS_LOG_WARN("sFlowIdx "<<(int) m_lastUsedsFlowIdx<<" -> Packet Droped !");
+               }
+           }else
+           {
+               m_mptcp->SendPacket (pkt, header, sAddr, dAddr);
+           }
+ 
+         NS_LOG_WARN (Simulator::Now().GetSeconds() <<" SentSegment -> "<< " m_localToken "<< m_localToken<<" Subflow "<<(int) m_lastUsedsFlowIdx<<" DataTxSeq "<<nextTxSequence<<" SubflowTxSeq "<<sFlow->TxSeqNumber<<" SubflowRxSeq "<< sFlow->RxSeqNumber <<" Data "<< size <<" unAcked Data " << unAckedDataCount <<" octets" );
+ 
+         // Notify the application of the data being sent
+         sFlow->rtt->SentSeq (SequenceNumber32(sFlow->TxSeqNumber), size);           // notify the RTT
+         nOctetsSent        += size;                               // Count sent this loop
+         nextTxSequence     += size;                // Advance next tx sequence
+         sFlow->TxSeqNumber += size;
+         sFlow->maxSeqNb    += size;
+         unAckedDataCount   += size;
+       }
+       m_lastUsedsFlowIdx = getSubflowToUse ();
+   }
+   NS_LOG_LOGIC ("RETURN SendPendingData -> amount data sent = " << nOctetsSent);
+   NotifyDataSent( GetTxAvailable() );
+ 
+   return ( nOctetsSent>0 );
+ }
+ 
+ uint8_t
+ MpTcpSocketBase::getSubflowToUse ()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     uint8_t nextSubFlow = 0;
+     switch ( m_distribAlgo )
+     {
+         case Round_Robin :
+             nextSubFlow = (m_lastUsedsFlowIdx + 1) % subflows.size();
+             break;
+         default:
+             break;
+     }
+     return nextSubFlow;
+ }
+ 
+ void
+ MpTcpSocketBase::ReTxTimeout (uint8_t sFlowIdx)
+ { // Retransmit timeout
+   //NS_LOG_INFO("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
+   NS_LOG_FUNCTION (this);
+   MpTcpSubFlow *sFlow = subflows[sFlowIdx];
+   NS_LOG_WARN ("Subflow ("<<(int)sFlowIdx<<") ReTxTimeout Expired at time "<<Simulator::Now ().GetSeconds()<< " unacked packets count is "<<sFlow->mapDSN.size() );
+ 
+   // If erroneous timeout in closed/timed-wait state, just return
+   if (m_state == CLOSED || m_state == TIME_WAIT)
+   {
+       NS_LOG_WARN ("ReTxTimeout subflow ("<<(int)sFlowIdx<<") current state is "<<m_stateMachine->printState(m_state));
+       return;
+   }
+   reduceCWND (sFlowIdx);
+   // Set cWnd to segSize on timeout,  per rfc2581
+   // Collapse congestion window (re-enter slowstart)
+ 
+   Retransmit (sFlowIdx);             // Retransmit the packet
+   if( m_algoPR == F_RTO )
+   {
+       sFlow->SpuriousRecovery = false;
+       if( (sFlow->phase == RTO_Recovery) && (sFlow->recover >= sFlow->highestAck + 1) )
+       {
+           sFlow->recover  = sFlow->TxSeqNumber; // highest sequence number transmitted
+           sFlow->ackCount = 0;
+           frtoStep = Step_4;    // go to step 4 to perform the standard Fast Recovery algorithm
+       }else
+       {
+           frtoStep = Step_2;    // enter step 2 of the F-RTO algorithm
+           NS_LOG_WARN("Entering step 2 of the F-RTO algorithm");
+       }
+       sFlow->phase = RTO_Recovery; // in RTO recovery algorithm, sender do slow start retransmissions
+   }
+ }
+ 
+ void
+ MpTcpSocketBase::reduceCWND (uint8_t sFlowIdx)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     MpTcpSubFlow *sFlow = subflows[sFlowIdx];
+     double cwnd = sFlow->cwnd;
+     calculateTotalCWND ();
+ 
+     // save current congestion state
+     switch ( m_algoPR )
+     {
+         case D_SACK:
+             sFlow->savedCWND = std::max (cwnd, sFlow->savedCWND);
+             sFlow->savedSSThresh = std::max(sFlow->ssthresh, sFlow->savedSSThresh);
+             break;
+         default:
+             sFlow->savedCWND = cwnd;
+             sFlow->savedSSThresh = sFlow->ssthresh;
+             break;
+     }
+ 
+ 
+     sFlow->ssthresh = (std::min(remoteRecvWnd, static_cast<uint32_t>(sFlow->cwnd))) / 2; // Per RFC2581
+     sFlow->ssthresh = std::max (sFlow->ssthresh, 2 * sFlow->MSS);
+ 
+     double gThroughput = getGlobalThroughput();
+     uint64_t lDelay = getPathDelay(sFlowIdx);
+ 
+     switch ( m_algoCC )
+     {
+         case Uncoupled_TCPs:
+             sFlow->cwnd  = std::max (cwnd  / 2, 1.0);
+             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" MpTcpSocketBase -> "<< " m_localToken "<< m_localToken<<" Subflow "<< (int)sFlowIdx <<": RTT "<< sFlow->rtt->GetCurrentEstimate().GetSeconds() <<" reducing cwnd from " << cwnd << " to "<<sFlow->cwnd <<" Throughput "<< (sFlow->cwnd * sFlow->MSS * 8) / sFlow->rtt->GetCurrentEstimate().GetSeconds()<< " GlobalThroughput "<<gThroughput<< " Efficacity " <<  getConnectionEfficiency() << " delay "<<lDelay << " Uncoupled_TCPs" );
+             break;
+         case Linked_Increases:
+             sFlow->cwnd  = std::max (cwnd  / 2, 1.0);
+             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" MpTcpSocketBase -> "<< " m_localToken "<< m_localToken<<" Subflow "<< (int)sFlowIdx <<": RTT "<< sFlow->rtt->GetCurrentEstimate().GetSeconds() <<" reducing cwnd from " << cwnd << " to "<<sFlow->cwnd <<" Throughput "<< (sFlow->cwnd * sFlow->MSS * 8) / sFlow->rtt->GetCurrentEstimate().GetSeconds() << " GlobalThroughput "<<gThroughput<< " Efficacity " <<  getConnectionEfficiency() << " delay "<<lDelay <<" alpha "<< alpha << " Linked_Increases");
+             break;
+         case RTT_Compensator:
+             sFlow->cwnd  = std::max (cwnd  / 2, 1.0);
+             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" MpTcpSocketBase -> "<< " m_localToken "<< m_localToken<<" Subflow "<< (int)sFlowIdx <<": RTT "<< sFlow->rtt->GetCurrentEstimate().GetSeconds() <<" reducing cwnd from " << cwnd << " to "<<sFlow->cwnd <<" Throughput "<< (sFlow->cwnd * sFlow->MSS * 8) / sFlow->rtt->GetCurrentEstimate().GetSeconds() << " GlobalThroughput "<<gThroughput<< " Efficacity " <<  getConnectionEfficiency() << " delay "<<lDelay <<" alpha "<< alpha << " RTT_Compensator");
+             break;
+         case Fully_Coupled:
+             sFlow->cwnd  = std::max (cwnd - totalCwnd / 2, 1.0);
+             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" MpTcpSocketBase -> "<< " m_localToken "<< m_localToken<<" Subflow "<< (int)sFlowIdx <<": RTT "<< sFlow->rtt->GetCurrentEstimate().GetSeconds() <<" reducing cwnd from " << cwnd << " to "<<sFlow->cwnd <<" Throughput "<< (sFlow->cwnd * sFlow->MSS * 8) / sFlow->rtt->GetCurrentEstimate().GetSeconds() << " GlobalThroughput "<<gThroughput<< " Efficacity " <<  getConnectionEfficiency() << " delay "<<lDelay <<" alpha "<< alpha << " Fully_Coupled");
+             break;
+         default:
+             sFlow->cwnd  = 1;
+             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" MpTcpSocketBase -> "<< " m_localToken "<< m_localToken<<" Subflow "<< (int)sFlowIdx <<": RTT "<<sFlow->rtt->GetCurrentEstimate().GetSeconds() <<" reducing cwnd from " << cwnd << " to "<<sFlow->cwnd <<" Throughput "<< (sFlow->cwnd * sFlow->MSS * 8) / sFlow->rtt->GetCurrentEstimate().GetSeconds() << " GlobalThroughput "<<gThroughput<< " Efficacity " <<  getConnectionEfficiency() << " delay "<<lDelay << " default");
+             break;
+     }
+ 
+     sFlow->phase = Congestion_Avoidance;
+     // sFlow->TxSeqNumber = sFlow->highestAck + 1; // Start from highest Ack
+     sFlow->rtt->IncreaseMultiplier (); // DoubleValue timeout value for next retx timer
+ }
+ 
+ void
+ MpTcpSocketBase::Retransmit (uint8_t sFlowIdx)
+ {
+   NS_LOG_FUNCTION (this);
+   MpTcpSubFlow *sFlow = subflows[sFlowIdx];
+   uint8_t flags = TcpHeader::ACK;
+   uint8_t hlen = 5;
+   uint8_t olen = 15;
+   uint8_t plen = 0;
+ 
+   //NS_ASSERT(sFlow->TxSeqNumber == sFlow->RxSeqNumber);
+   DSNMapping * ptrDSN = sFlow->GetunAckPkt (AvailableWindow (sFlowIdx));
+   if (ptrDSN == 0)
+   {
+       NS_LOG_WARN ("Retransmit -> no Unacked data !! mapDSN size is "<< sFlow->mapDSN.size() << " max Ack seq n° "<< sFlow->highestAck);
+       return;
+   }
+   // Calculate remaining data for COE check
+   Ptr<Packet> pkt = new Packet (ptrDSN->packet, ptrDSN->dataLevelLength);
+ 
+   NS_LOG_WARN (Simulator::Now().GetSeconds() <<" RetransmitSegment -> "<< " m_localToken "<< m_localToken<<" Subflow "<<(int) sFlowIdx<<" DataSeq "<< ptrDSN->dataSeqNumber <<" SubflowSeq " << ptrDSN->subflowSeqNumber <<" dataLength " << ptrDSN->dataLevelLength << " packet size " << pkt->GetSize() <<" RTO_Timeout" );
+ 
+   SetReTxTimeout (sFlowIdx);
+ 
+   //sFlow->rtt->SentSeq (ptrDSN->subflowSeqNumber, ptrDSN->dataLevelLength);
+   sFlow->rtt->pktRetransmit (SequenceNumber32(ptrDSN->subflowSeqNumber));
+ 
+   // And send the packet
+   MpTcpHeader mptcpHeader;
+   mptcpHeader.SetSequenceNumber  (SequenceNumber32(ptrDSN->subflowSeqNumber));
+   mptcpHeader.SetAckNumber       (SequenceNumber32(sFlow->RxSeqNumber));
+   mptcpHeader.SetSourcePort      (sFlow->sPort);
+   mptcpHeader.SetDestinationPort (sFlow->dPort);
+   mptcpHeader.SetFlags           (flags);
+   mptcpHeader.SetWindowSize      (AdvertisedWindowSize());
+ 
+     mptcpHeader.AddOptDSN (OPT_DSN, ptrDSN->dataSeqNumber, ptrDSN->dataLevelLength, ptrDSN->subflowSeqNumber);
+ 
+     switch ( m_algoPR )
+     {
+         case Eifel:
+             if(ptrDSN->retransmited == false)
+             {
+                 ptrDSN->retransmited = true;
+                 ptrDSN->tsval = Simulator::Now ().GetMilliSeconds (); // update timestamp value to the current time
+             }
+             mptcpHeader.AddOptTT  (OPT_TT, ptrDSN->tsval, 0);
+             olen += 17;
+             break;
+         case D_SACK:
+             if(ptrDSN->retransmited == false)
+             {
+                 ptrDSN->retransmited = true;
+                 retransSeg[ptrDSN->dataSeqNumber] = ptrDSN->dataLevelLength;
+             }
+             break;
+         case F_RTO:
+             sFlow->ReTxSeqNumber = std::max(sFlow->ReTxSeqNumber, ptrDSN->subflowSeqNumber + ptrDSN->dataLevelLength);
+             break;
+         default:
+             break;
+     }
+ 
+     plen = (4 - (olen % 4)) % 4;
+     olen = (olen + plen) / 4;
+     hlen += olen;
+     mptcpHeader.SetLength(hlen);
+     mptcpHeader.SetOptionsLength(olen);
+     mptcpHeader.SetPaddingLength(plen);
+ 
+   m_mptcp->SendPacket (pkt, mptcpHeader, sFlow->sAddr, sFlow->dAddr);
+   //delete ptrDSN; // if you want let it you've to uncomment 'mapDSN.erase (it)' in method GetunAckPkt
+ }
+ 
+ void
+ MpTcpSocketBase::SetReTxTimeout (uint8_t sFlowIdx)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     MpTcpSubFlow *sFlow = subflows[sFlowIdx];
+     if ( sFlow->retxEvent.IsExpired () )
+     {
+         Time rto = sFlow->rtt->RetransmitTimeout ();
+         	//rto=Seconds(0.2);  //Pablo uc
+         NS_LOG_INFO ("Schedule ReTxTimeout subflow ("<<(int)sFlowIdx<<") at time " << Simulator::Now ().GetSeconds () << " after rto ("<<rto.GetSeconds ()<<") at " << (Simulator::Now () + rto).GetSeconds ());
+         sFlow->retxEvent = Simulator::Schedule (rto,&MpTcpSocketBase::ReTxTimeout,this, sFlowIdx);
+     }
+ }
+ 
+ bool
+ MpTcpSocketBase::ProcessAction (uint8_t sFlowIdx, Actions_t a)
+ {
+     //NS_LOG_FUNCTION (this << m_node->GetId()<< sFlowIdx <<m_stateMachine->printAction(a) << a );
+     MpTcpSubFlow * sFlow = subflows[sFlowIdx];
+     bool result = true;
+     switch (a)
+     {
+         case SYN_TX:
+             NS_LOG_LOGIC ("MpTcpSocketBase"<<m_node->GetId()<<" " << this <<" Action: SYN_TX, Subflow: "<<sFlowIdx);
+             SendEmptyPacket (sFlowIdx, TcpHeader::SYN);
+             break;
+ 
+         case ACK_TX:
+             // this acknowledgement is not part of the handshake process
+             NS_LOG_LOGIC ("MpTcpSocketBase " << this <<" Action ACK_TX");
+             SendEmptyPacket (sFlowIdx, TcpHeader::ACK);
+             break;
+ 
+         case FIN_TX:
+             NS_LOG_LOGIC ("MpTcpSocketBase "<<m_node->GetId()<<" "  << this <<" Action FIN_TX");
+             NS_LOG_INFO  ("Number of rejected packet ("<<nbRejected<< ") total received packet (" << nbReceived <<")");
+             SendEmptyPacket (sFlowIdx, TcpHeader::FIN);
+             break;
+ 
+         case FIN_ACK_TX:
+             NS_LOG_LOGIC ("MpTcpSocketBase "<<m_node->GetId()<<" "  << this <<" Action FIN_ACK_TX");
+             NS_LOG_INFO  ("Number of rejected packet ("<<nbRejected<< ") total received packet (" << nbReceived <<")");
+             SendEmptyPacket (sFlowIdx, TcpHeader::FIN | TcpHeader::ACK);
+             CloseMultipathConnection();
+             sFlow->state = CLOSED;
+             break;
+ 
+         case TX_DATA:
+             NS_LOG_LOGIC ("MpTcpSocketBase "<<m_node->GetId()<<" "  << this <<" Action TX_DATA");
+             result = SendPendingData ();
+             break;
+ 
+         default:
+             NS_LOG_LOGIC ("MpTcpSocketBase "<<m_node->GetId()<<": " << this <<" Action: " << m_stateMachine->printAction(a) << " ( " << a << " )" << " not handled");
+             break;
+     }
+     return result;
+ }
+ 
+ bool
+ MpTcpSocketBase::ProcessAction (uint8_t sFlowIdx, MpTcpHeader mptcpHeader, Ptr<Packet> pkt, uint32_t dataLen, Actions_t a)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     //NS_LOG_FUNCTION (this << m_node->GetId()<< sFlowIdx <<m_stateMachine->printAction(a) << a );
+     MpTcpSubFlow * sFlow = subflows[sFlowIdx];
+     bool result = true;
+     uint32_t seq = 0;
+     Time t;
+     switch (a)
+     {
+         case ACK_TX_1:
+             NS_LOG_LOGIC ("MpTcpSocketBase"<<m_node->GetId()<<" " << this <<" Action: ACK_TX_1");
+             // TCP SYN consumes one byte
+             if( sFlowIdx == 0)
+                 seq = 2;
+             else
+                 //seq = 2;
+                 seq = 1; // because we send only ACK (1 packet)
+ 
+             NS_LOG_INFO ("initiating RTO for subflow ("<< (int) sFlowIdx <<") with seq "<<sFlow->TxSeqNumber);
+             sFlow->rtt->Init( mptcpHeader.GetAckNumber () + SequenceNumber32(seq) ); // initialize next with the next seq number to be sent
+ 
+             //sFlow->rtt->est =  TimeUnit<1>("1.5s");
+ 
+             //t=Seconds(1.5);
+             sFlow->rtt->SetCurrentEstimate(t);
+ 
+             sFlow->RxSeqNumber =  (mptcpHeader.GetSequenceNumber()).GetValue () + 1;
+             sFlow->highestAck  = std::max ( sFlow->highestAck, (mptcpHeader.GetAckNumber ()).GetValue() - 1 );
+ 
+             SendEmptyPacket (sFlowIdx, TcpHeader::ACK);
+             if(m_addrAdvertised == false)
+             {
+                 AdvertiseAvailableAddresses();
+                 m_addrAdvertised = true;
+             }
+             m_aggregatedBandwidth += sFlow->bandwidth;
+             // when a single path is established between endpoints then we can say the connection is established
+             if(m_state != ESTABLISHED)
+                 NotifyConnectionSucceeded ();
+ 
+             m_state = ESTABLISHED;
+             sFlow->StartTracing ("CongestionWindow");
+             break;
+ 
+         case SYN_ACK_TX:
+             NS_LOG_INFO ("MpTcpSocketBase("<<m_node->GetId()<<") sFlowIdx("<< (int) sFlowIdx <<") Action SYN_ACK_TX");
+             // TCP SYN consumes one byte
+             sFlow->RxSeqNumber = (mptcpHeader.GetSequenceNumber()).GetValue() + 1 ;
+             sFlow->highestAck  = std::max ( sFlow->highestAck, (mptcpHeader.GetAckNumber ()).GetValue() - 1 );
+             SendEmptyPacket (sFlowIdx, TcpHeader::SYN | TcpHeader::ACK);
+             break;
+ 
+         case NEW_SEQ_RX:
+             NS_LOG_LOGIC ("MpTcpSocketBase::ProcessAction -> " << this <<" Action NEW_SEQ_RX already processed in ProcessHeaderOptions");
+             // Process new data received
+             break;
+ 
+         case NEW_ACK:
+             // action performed by receiver
+             NS_LOG_LOGIC ("MpTcpSocketBase::ProcessAction -> " << this <<" Action NEW_ACK");
+             NewACK (sFlowIdx, mptcpHeader, 0);
+             break;
+ 
+         case SERV_NOTIFY:
+             // the receiver had received the ACK confirming the establishment of the connection
+             NS_LOG_LOGIC ("MpTcpSocketBase  Action SERV_NOTIFY -->  Connected!");
+             sFlow->RxSeqNumber = (mptcpHeader.GetSequenceNumber()).GetValue() + 1; // next sequence to receive
+             NS_LOG_LOGIC ("MpTcpSocketBase:Serv_Notify next ACK will be = " << sFlow->RxSeqNumber);
+             sFlow->highestAck  = std::max ( sFlow->highestAck, (mptcpHeader.GetAckNumber ()).GetValue() - 1 );
+             sFlow->connected   = true;
+             if(m_connected != true)
+                 NotifyNewConnectionCreated (this, m_remoteAddress);
+             m_connected        = true;
+             break;
+ 
+         default:
+             result = ProcessAction ( sFlowIdx, a);
+             break;
+     }
+     return result;
+ }
+ 
+ DSNMapping*
+ MpTcpSocketBase::getAckedSegment(uint8_t sFlowIdx, uint32_t ack)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     MpTcpSubFlow* sFlow = subflows[sFlowIdx];
+     DSNMapping* ptrDSN = 0;
+     for (list<DSNMapping *>::iterator it = sFlow->mapDSN.begin(); it != sFlow->mapDSN.end(); ++it)
+     {
+         DSNMapping* dsn = *it;
+         if(dsn->subflowSeqNumber + dsn->dataLevelLength == ack)
+         {
+             ptrDSN = dsn;
+             break;
+         }
+     }
+     return ptrDSN;
+ }
+ 
+ void
+ MpTcpSocketBase::NewACK (uint8_t sFlowIdx, MpTcpHeader mptcpHeader, TcpOptions *opt)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     MpTcpSubFlow * sFlow = subflows[sFlowIdx];
+     uint32_t ack = (mptcpHeader.GetAckNumber ()).GetValue();
+     uint32_t ackedBytes = ack - sFlow->highestAck - 1;
+     DSNMapping* ptrDSN = getAckedSegment(sFlowIdx, ack);
+ 
+ 
+     if (m_algoPR == F_RTO)
+     {
+         uint16_t nbP[] = {389, 211, 457, 277, 367, 479, 233}; // some prime numbers
+         double threshold = 0.061 * (((double) (((int) time (NULL)) % nbP[sFlowIdx])) / (double) nbP[sFlowIdx]);
+         if(sFlow->nbRecvAck == -1)
+             sFlow->nbRecvAck = (rejectPacket(threshold)==true ? 0:-1);
+         else
+         {
+             sFlow->nbRecvAck++;
+             if(sFlow->nbRecvAck < sFlow->cwnd)
+             {
+                 return;
+             }else
+             {
+                 sFlow->nbRecvAck = -1;
+             }
+         }
+     }
+     if( (opt != 0) && (opt->optName == OPT_DSACK) )
+     {
+         OptDSACK* dsack = (OptDSACK*) opt;
+         NS_LOG_WARN (Simulator::Now().GetSeconds() <<" DSACK_option -> Subflow "<<(int)sFlowIdx<<" 1stBlock lowerEdge "<<dsack->blocks[0]<<" upperEdge "<<dsack->blocks[1]<<" / 2ndBlock lowerEdge " << dsack->blocks[3] <<" upperEdge " << dsack->blocks[4] );
+         DSNMapping* dsn = getAckedSegment(dsack->blocks[0], dsack->blocks[1]);
+         if(ptrDSN != 0)
+             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" Cumulative_ACK -> "<< " m_localToken "<< m_localToken<<" Subflow "<<(int)sFlowIdx<<" Data_ACK "<<ptrDSN->dataSeqNumber + ptrDSN->dataLevelLength <<" Subflow_ACK "<< ack <<" Data_DSACK "<<dsack->blocks[0]<<" "<<dsack->blocks[1]<<" Subflow_DSACK "<<dsn->subflowSeqNumber<<" "<<dsn->subflowSeqNumber + dsn->dataLevelLength<<" highestAckedData " << sFlow->highestAck<<" maxSequenNumber " << sFlow->maxSeqNb <<" AckedData " << ackedBytes << " unAckedData " << ( sFlow->maxSeqNb - sFlow->highestAck ));
+         else
+             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" Cumulative_ACK -> "<< " m_localToken "<< m_localToken<<" Subflow "<<(int)sFlowIdx<<" Data_ACK ? Subflow_ACK "<< ack <<" Data_DSACK "<<dsack->blocks[0]<<" "<<dsack->blocks[1]<<" Subflow_DSACK "<<dsn->subflowSeqNumber<<" "<<dsn->subflowSeqNumber + dsn->dataLevelLength<<" highestAckedData " << sFlow->highestAck<<" maxSequenNumber " << sFlow->maxSeqNb <<" AckedData " << ackedBytes << " unAckedData " << ( sFlow->maxSeqNb - sFlow->highestAck ));
+     }else
+     {
+         if(ptrDSN != 0)
+             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" Cumulative_ACK -> "<< " m_localToken "<< m_localToken<<" Subflow "<<(int)sFlowIdx<<" Data_ACK "<<ptrDSN->dataSeqNumber + ptrDSN->dataLevelLength <<" Subflow_ACK "<< ack <<" highestAckedData " << sFlow->highestAck<<" maxSequenNumber " << sFlow->maxSeqNb <<" AckedData " << ackedBytes << " unAckedData " << ( sFlow->maxSeqNb - sFlow->highestAck ));
+         else
+             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" Cumulative_ACK -> "<< " m_localToken "<< m_localToken<<" Subflow "<<(int)sFlowIdx<<" Data_ACK ? Subflow_ACK "<< ack <<" highestAckedData " << sFlow->highestAck<<" maxSequenNumber " << sFlow->maxSeqNb <<" AckedData " << ackedBytes << " unAckedData " << ( sFlow->maxSeqNb - sFlow->highestAck ));
+     }
+ 
+     if( IsDuplicatedAck(sFlowIdx, mptcpHeader, opt) == false )
+     {
+         sFlow->retxEvent.Cancel (); //On recieving a "New" ack we restart retransmission timer .. RFC 2988
+ 
+         sFlow->updateRTT      ((mptcpHeader.GetAckNumber()).GetValue(), Simulator::Now ());
+         sFlow->RxSeqNumber  = (mptcpHeader.GetSequenceNumber()).GetValue() + 1;
+         sFlow->highestAck   = std::max ( sFlow->highestAck, ack - 1 );
+         unAckedDataCount    = ( sFlow->maxSeqNb - sFlow->highestAck ) ;
+ 
+         if ( unAckedDataCount > 0 )
+         {
+             Time rto = sFlow->rtt->RetransmitTimeout ();
+             NS_LOG_LOGIC ("Schedule ReTxTimeout at " << Simulator::Now ().GetSeconds () << " to expire at " << (Simulator::Now () + rto).GetSeconds () <<" unAcked data "<<unAckedDataCount);
+             sFlow->retxEvent = Simulator::Schedule (rto, &MpTcpSocketBase::ReTxTimeout, this, sFlowIdx);
+         }
+         // you have to move the idxBegin of the sendingBuffer by the amount of newly acked data
+         OpenCWND (sFlowIdx, ackedBytes);
+         NotifyDataSent ( GetTxAvailable() );
+         SendPendingData ();
+     }else if( (useFastRecovery == true) || (m_algoPR == F_RTO && frtoStep == Step_4) )
+     {
+         // remove sequence gap from DNSMap list
+         NS_LOG_WARN (Simulator::Now ().GetSeconds () << " Fast Recovery -> duplicated ACK ("<< (mptcpHeader.GetAckNumber ()).GetValue() <<")");
+         OpenCWND (sFlowIdx, 0);
+         SendPendingData ();
+     }
+ }
+ 
+ Actions_t
+ MpTcpSocketBase::ProcessEvent (uint8_t sFlowId, Events_t e)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     //NS_LOG_FUNCTION(this << (int) sFlowId << m_stateMachine->printEvent(e));
+     MpTcpSubFlow * sFlow = subflows[sFlowId];
+     if( sFlow == 0 )
+         return NO_ACT;
+     TcpStates_t previous = sFlow->state;
+     SA sAct = m_stateMachine->Lookup(sFlow->state, e);
+     if( previous == LISTEN && sAct.state == SYN_RCVD && sFlow->connected == true )
+         return NO_ACT;
+ 
+     sFlow->state = sAct.state;
+     NS_LOG_LOGIC ("MpTcpSocketBase"<<m_node->GetId()<<":ProcessEvent Moved from subflow "<<(int)sFlowId <<" state " << m_stateMachine->printState(previous) << " to " << m_stateMachine->printState(sFlow->state));
+ 
+     if (!m_connected && previous == SYN_SENT && sFlow->state == ESTABLISHED)
+     {
+         // this means the application side has completed its portion of the handshaking
+         //Simulator::ScheduleNow(&NotifyConnectionSucceeded(), this);
+         m_connected = true;
+         m_endPoint->SetPeer (m_remoteAddress, m_remotePort);
+     }
+     return sAct.action;
+ }
+ 
+ void
+ MpTcpSocketBase::SendEmptyPacket (uint8_t sFlowId, uint8_t flags)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+   //NS_LOG_FUNCTION (this << (int) sFlowId << (uint32_t)flags);
+   MpTcpSubFlow *sFlow = subflows[sFlowId];
+   Ptr<Packet> p = new Packet(0); //Create<Packet> ();
+   MpTcpHeader header;
+   uint8_t hlen = 0;
+   uint8_t olen = 0;
+ 
+   header.SetSourcePort      (sFlow->sPort);
+   header.SetDestinationPort (sFlow->dPort);
+   header.SetFlags           (flags);
+   header.SetSequenceNumber  (SequenceNumber32(sFlow->TxSeqNumber));
+   header.SetAckNumber       (SequenceNumber32(sFlow->RxSeqNumber));
+   header.SetWindowSize      (AdvertisedWindowSize());
+ 
+   if(((sFlow->state == SYN_SENT) || (sFlow->state==SYN_RCVD && m_mpEnabled==true)) && m_mpSendState==MP_NONE)
+   {
+       m_mpSendState = MP_MPC;
+       m_localToken  = rand() % 1000;
+       header.AddOptMPC(OPT_MPC, m_localToken);
+       olen += 5;
+   }
+ 
+   uint8_t plen = (4 - (olen % 4)) % 4;
+   // urgent pointer
+   // check sum filed
+   olen = (olen + plen) / 4;
+   hlen = 5 + olen;
+   header.SetLength(hlen);
+   header.SetOptionsLength(olen);
+   header.SetPaddingLength(plen);
+ 
+   //SetReTxTimeout (sFlowId);
+ 
+   m_mptcp->SendPacket (p, header, sFlow->sAddr, sFlow->dAddr);
+   //sFlow->rtt->SentSeq (sFlow->TxSeqNumber, 1);           // notify the RTT
+   sFlow->TxSeqNumber++;
+   sFlow->maxSeqNb++;
+   //unAckedDataCount++;
+ }
+ 
+ void
+ MpTcpSocketBase::SendAcknowledge (uint8_t sFlowId, uint8_t flags, TcpOptions *opt)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+   //NS_LOG_FUNCTION (this << (int) sFlowId << (uint32_t)flags);
+   NS_LOG_INFO ("sending acknowledge segment with option");
+   MpTcpSubFlow *sFlow = subflows[sFlowId];
+   Ptr<Packet> p = new Packet(0); //Create<Packet> ();
+   MpTcpHeader header;
+   uint8_t hlen = 0;
+   uint8_t olen = 0;
+ 
+   header.SetSourcePort      (sFlow->sPort);
+   header.SetDestinationPort (sFlow->dPort);
+   header.SetFlags           (flags);
+   header.SetSequenceNumber  (SequenceNumber32(sFlow->TxSeqNumber));
+   header.SetAckNumber       (SequenceNumber32(sFlow->RxSeqNumber));
+   header.SetWindowSize      (AdvertisedWindowSize());
+ 
+     switch ( m_algoPR )
+     {
+         case Eifel:
+             header.AddOptTT (OPT_TT, ((OptTimesTamp *) opt)->TSval, ((OptTimesTamp *) opt)->TSecr);
+             olen += 17;
+             // I've to think about if I can increment or not the sequence control parameters
+             sFlow->TxSeqNumber++;
+             sFlow->maxSeqNb++;
+             break;
+         case D_SACK:
+             header.AddOptDSACK (OPT_DSACK, (OptDSACK *) opt);
+             olen += 33;
+             break;
+         default:
+             break;
+     }
+ 
+   uint8_t plen = (4 - (olen % 4)) % 4;
+   // urgent pointer
+   // check sum filed
+   olen = (olen + plen) / 4;
+   hlen = 5 + olen;
+   header.SetLength(hlen);
+   header.SetOptionsLength(olen);
+   header.SetPaddingLength(plen);
+   m_mptcp->SendPacket (p, header, sFlow->sAddr, sFlow->dAddr);
+ 
+ }
+ 
+ void
+ MpTcpSocketBase::allocateSendingBuffer (uint32_t size)
+ {
+ 
+     NS_LOG_FUNCTION(this << size);
+     sendingBuffer = new DataBuffer(size);
+ }
+ 
+ void
+ MpTcpSocketBase::allocateRecvingBuffer (uint32_t size)
+ {
+     NS_LOG_FUNCTION(this << size);
+     recvingBuffer = new DataBuffer(size);
+ }
+ 
+ void
+ MpTcpSocketBase::SetunOrdBufMaxSize (uint32_t size)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     unOrdMaxSize = size;
+ }
+ 
+ uint32_t
+ MpTcpSocketBase::Recv (uint8_t* buf, uint32_t size)
+ {
+   NS_LOG_FUNCTION (this << size);
+   //Null packet means no data to read, and an empty packet indicates EOF
+   uint32_t toRead = std::min( recvingBuffer->PendingData() , size);
+   return recvingBuffer->Retrieve(buf, toRead);
+ }
+ 
+ void
+ //MpTcpSocketBase::ForwardUp (Ptr<Packet> p, Ipv4Address ipv4Remote, uint16_t port, Ptr<Ipv4Interface> inter)
+ 
+ MpTcpSocketBase::ForwardUp (Ptr<Packet> p, Ipv4Header ipv4Head, uint16_t port, Ptr<Ipv4Interface> inter)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+ 
+   Ipv4Address ipv4Remote;
+   ipv4Remote=ipv4Head.GetSource();
+ 
+   m_remoteAddress = ipv4Remote; //m_endPoint->GetPeerAddress();
+ 
+   m_remotePort    = m_endPoint->GetPeerPort();
+   m_localAddress  = m_endPoint->GetLocalAddress();
+ 
+   uint8_t sFlowIdx = LookupByAddrs(m_localAddress, ipv4Remote); //m_endPoint->GetPeerAddress());
+ 
+   if(! (sFlowIdx < m_maxSubFlowNumber) )
+       return;
+ 
+   MpTcpSubFlow *sFlow = subflows[sFlowIdx];
+ 
+   MpTcpHeader mptcpHeader;
+   p->RemoveHeader (mptcpHeader);
+ 
+   uint32_t dataLen;   // packet's payload length
+   remoteRecvWnd = (uint32_t) mptcpHeader.GetWindowSize (); //update the flow control window
+ 
+   //Events_t event = SimulationSingleton<TcpStateMachine>::Get ()->FlagsEvent (tcpHeader.GetFlags () );
+   sFlow->dAddr = ipv4Remote;//m_endPoint->GetPeerAddress();
+   sFlow->dPort = m_endPoint->GetPeerPort();
+   // process the options in the header
+   Actions_t action = ProcessHeaderOptions(sFlowIdx, p, &dataLen, mptcpHeader);
+ 
+   //NS_LOG_INFO("MpTcpSocketBase"<<m_node->GetId()<<":ForwardUp Socket " << this << " ( current state " << m_stateMachine->printState( sFlow->state ) << " ) -> processing packet action is " << m_stateMachine->printAction( action ) );
+ 
+   ProcessAction (sFlowIdx, mptcpHeader, p, dataLen, action);
+ }
+ 
+ void
+ MpTcpSocketBase::ProcessMultipathState ()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     switch(m_mpState)
+     {
+         case MP_ADDR:
+             m_mpState = MP_JOIN;
+             InitiateSubflows();
+             break;
+         default:
+             break;
+     }
+ }
+ 
+ bool
+ MpTcpSocketBase::InitiateSubflows ()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     bool result = true;
+     for(uint32_t i =0; i < localAddrs.size(); i++)
+     for(uint32_t j =i; j < remoteAddrs.size(); j++)
+     {
+         uint8_t addrID     = localAddrs[i]->addrID;
+         Ipv4Address local  = localAddrs[i]->ipv4Addr;
+         Ipv4Address remote = remoteAddrs[j]->ipv4Addr;
+ 
+         // skip already established flows
+         if( ((local == m_localAddress) && (remote == m_remoteAddress)) || (!IsThereRoute(local, remote)))
+             continue;
+ NS_LOG_LOGIC ("IsThereRoute -> Route from srcAddr "<< local << " to dstAddr " << remote <<", exist !");
+         uint32_t initSeqNb = rand() % 1000 + (sfInitSeqNb.size() +1 ) * 10000;
+         sfInitSeqNb[local] = initSeqNb;
+         Ptr<Packet> pkt = Create<Packet> ();
+         MpTcpHeader header;
+         header.SetFlags           (TcpHeader::SYN);//flags);
+         header.SetSequenceNumber  (SequenceNumber32(initSeqNb));
+         header.SetAckNumber       (SequenceNumber32(subflows[0]->RxSeqNumber));
+         // endpoints port number remain unchangeable
+         header.SetSourcePort      (m_endPoint->GetLocalPort ());
+         header.SetDestinationPort (m_remotePort);
+ 
+         header.AddOptJOIN         (OPT_JOIN, m_remoteToken, addrID);
+ 
+         uint8_t olen = 6;
+         uint8_t plen = (4 - (olen % 4)) % 4;
+ 
+         header.SetWindowSize ( AdvertisedWindowSize() );
+         // urgent pointer
+         // check sum filed
+         olen = (olen + plen) / 4;
+         uint8_t hlen = 5 + olen;
+         header.SetLength(hlen);
+         header.SetOptionsLength(olen);
+         header.SetPaddingLength(plen);
+ 
+         //SetReTxTimeout (sFlowIdx);
+         m_mptcp->SendPacket (pkt, header, local, remote);
+ NS_LOG_INFO("MpTcpSocketBase::InitiateSubflows -> (src, dst) = (" << local << ", " << remote << ") JOIN segment successfully sent !");
+ 
+     }
+     return result;
+ }
+ 
+ void
+ MpTcpSocketBase::calculateTotalCWND ()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     totalCwnd = 0;
+     for (uint32_t i = 0; i < subflows.size() ; i++)
+     {
+         totalCwnd += subflows[i]->cwnd;
+     }
+ }
+ 
+ Actions_t
+ MpTcpSocketBase::ProcessHeaderOptions (uint8_t sFlowIdx, Ptr<Packet> pkt, uint32_t *dataLen, MpTcpHeader mptcpHeader)
+ {
+     // packet is without header, see ForwardUp method
+     NS_LOG_FUNCTION(this);
+     MpTcpSubFlow * sFlow = subflows[sFlowIdx];
+     vector< TcpOptions* > options = mptcpHeader.GetOptions();
+     uint8_t flags = mptcpHeader.GetFlags ();
+ 
+   Actions_t action = ProcessEvent (sFlowIdx, m_stateMachine->FlagsEvent (flags)); //updates the state
+   //NS_LOG_INFO("MpTcpSocketBase::ProcessHeaderOptions-> event  ("<< m_stateMachine->printEvent(m_stateMachine->FlagsEvent (flags))<<") => action = "<< m_stateMachine->printAction( action ));
+   int length = 0;
+   TcpOptions *opt, *opt1;
+ 
+   bool hasSyn = flags &  TcpHeader::SYN;
+   //bool hasFin = flags &  TcpHeader::FIN;
+   //bool isAck  = flags == TcpHeader::ACK;
+   bool TxAddr = false, TxACK = false, TxAckOpt = false;
+   bool initSubFlow = false;
+ 
+   for(uint32_t j = 0; j < options.size(); j++)
+   {
+       opt = options[j];
+ 
+       if ( (opt->optName == OPT_MPC) && hasSyn && (m_mpRecvState == MP_NONE) )
+       {
+           //NS_LOG_INFO("MpTcpSocketBase:ProcessHeaderOptions -> OPT_MPC received");
+           m_mpRecvState = MP_MPC;
+           m_mpEnabled   = true;
+           m_remoteToken = ((OptMultipathCapable *)opt)->senderToken;
+ //          initSubFlow = true;
+ 
+       }else if((opt->optName == OPT_JOIN) && hasSyn)
+       {
+           OptJoinConnection * optJoin = (OptJoinConnection *) opt;
+           if( (m_mpSendState == MP_ADDR) && (m_localToken == optJoin->receiverToken) )
+           {
+               // Join option is sent over the path (couple of addresses) not already in use
+               //NS_LOG_INFO ( "MpTcpSocketBase::ProcessHeaderOptions -> OPT_JOIN received");
+              initSubFlow = true;
+           }
+ 
+       }else if((opt->optName == OPT_ADDR) && (m_mpRecvState==MP_MPC))
+       {
+           // necessary action must be done here
+           TxAddr = true;
+           MpTcpAddressInfo * addrInfo = new MpTcpAddressInfo();
+           addrInfo->addrID   = ((OptAddAddress *)opt)->addrID;
+           addrInfo->ipv4Addr = ((OptAddAddress *)opt)->addr;
+           remoteAddrs.insert  (remoteAddrs.end(), addrInfo);
+           //NS_LOG_INFO ( "MpTcpSocketBase::ProcessHeaderOptions -> remote address " << addrInfo->ipv4Addr );
+       }else if(opt->optName == OPT_REMADR)
+       {
+           length += 2;
+       }else if(opt->optName == OPT_TT)
+       {
+           NS_LOG_INFO ("TCP TimesTamp option");
+           if(server == true)
+           {
+               opt1 = new OptTimesTamp (OPT_TT, Simulator::Now ().GetMilliSeconds (), ((OptTimesTamp *) opt)->TSval);
+           }else if(client == true)
+           {
+               NS_LOG_INFO ("This is a client");
+               opt1 = (OptTimesTamp *) opt;
+           }
+           TxAckOpt = true;
+       }else if (opt->optName == OPT_DSACK && client == true)
+       {
+           NS_LOG_INFO ("Client received DSACK option");
+           opt1 = (OptDSACK *) opt;
+           TxAckOpt = true;
+       }else if(opt->optName == OPT_DSN)
+       {
+           // data reception so threat it
+           OptDataSeqMapping * optDSN = (OptDataSeqMapping *) opt;
+           TxACK = true;
+           *dataLen = optDSN->dataLevelLength;
+           Ptr<Packet> packet = pkt;
+           uint32_t pktLen    = *dataLen;
+ 
+ NS_LOG_LOGIC("Multipath Seq N° dataSeqNumber (" << optDSN->dataSeqNumber <<") Seq N° nextRxSequence (" << nextRxSequence<<")   /   Subflow Seq N° RxSeqNumber (" << sFlow->RxSeqNumber << ") Seq N° subflowSeqNumber (" << optDSN->subflowSeqNumber<< ")");
+ 
+           if ( (m_algoPR == D_SACK) && (optDSN->dataSeqNumber > nextRxSequence) )
+           {
+               NS_LOG_DEBUG ("Subflow ("<<(int)sFlowIdx<<"): data arrived ("<< optDSN->dataSeqNumber <<") of length ("<< optDSN->dataLevelLength <<") buffered for subsequent reordering !");
+               StoreUnOrderedData (new DSNMapping(sFlowIdx, optDSN->dataSeqNumber, optDSN->dataLevelLength, optDSN->subflowSeqNumber,(mptcpHeader.GetAckNumber ()).GetValue(), pkt));
+               // send ACK with DSACK only for segment that also create a hole in the subflow level
+               //if(optDSN->subflowSeqNumber > sFlow->RxSeqNumber)
+               //{
+                   NS_LOG_DEBUG ("DSACK option to be created !");
+                   opt1 = createOptDSACK (optDSN);
+                   TxAckOpt = true;
+               //}
+               TxACK = false;
+           }else if( optDSN->subflowSeqNumber == sFlow->RxSeqNumber )
+           {
+               if( optDSN->dataSeqNumber == nextRxSequence )
+               {
+                   // it's ok for this data, send ACK( sFlowSeq + dataLevel) and save data to reception buffer
+                   NS_LOG_LOGIC("MpTcpSocketBase::ProcessHeaderOptions -> acknowledgment for data length ("<< optDSN->dataLevelLength <<") to be sent on subflow (" << (int) sFlowIdx << ") remote address (" << sFlow->dAddr<<")");
+ 
+                   uint32_t amountRead = recvingBuffer->ReadPacket (pkt, pktLen);
+                   sFlow->RxSeqNumber += amountRead;
+                   nextRxSequence     += amountRead;
+                   sFlow->highestAck   = std::max ( sFlow->highestAck, (mptcpHeader.GetAckNumber ()).GetValue() - 1 );
+                   // acknowledgement for this segment will be sent because we've already set TxACK
+                   ReadUnOrderedData ();
+                   NotifyDataRecv    ();
+ 
+               }else if( optDSN->dataSeqNumber > nextRxSequence )
+               {
+                   // it's ok for the subflow but not for the connection -> put the data on resequency buffer
+                   NS_LOG_DEBUG("Subflow ("<<(int)sFlowIdx<<"): data arrived ("<< optDSN->dataSeqNumber <<") of length ("<< optDSN->dataLevelLength <<") buffered for subsequent reordering !");
+                   TxACK = StoreUnOrderedData(new DSNMapping(sFlowIdx, optDSN->dataSeqNumber, optDSN->dataLevelLength, optDSN->subflowSeqNumber, (mptcpHeader.GetAckNumber ()).GetValue(), pkt));
+ 
+                   // we send an ACK back for the received segment not in sequence
+                   TxACK = false;
+                   //sFlow->RxSeqNumber += pktLen; // the received data is in sequence of the subflow => ack it's reception
+               }else
+               {
+                   NS_LOG_LOGIC("MpTcpSocketBase::ProcessHeaderOptions -> Subflow ("<<(int)sFlowIdx<<"): data received but duplicated, reject ("<<optDSN->subflowSeqNumber<<")");
+               }
+           }else if( optDSN->subflowSeqNumber > sFlow->RxSeqNumber )
+           {
+               NS_LOG_LOGIC("MpTcpSocketBase::ProcessHeaderOptions -> Subflow ("<<(int)sFlowIdx<<"): data arrived ("<<optDSN->subflowSeqNumber<<") causing potontial data lost !");
+               TxACK = StoreUnOrderedData(new DSNMapping(sFlowIdx, optDSN->dataSeqNumber, optDSN->dataLevelLength, optDSN->subflowSeqNumber, (mptcpHeader.GetAckNumber ()).GetValue(), pkt));
+               //TxACK = false;
+           }else
+           {
+               NS_LOG_LOGIC("MpTcpSocketBase::ProcessHeaderOptions -> Subflow ("<<(int)sFlowIdx<<"): data already received, reject !");
+               //action = NO_ACT;
+           }
+       }
+   }
+ 
+   if(TxAddr==true)
+   {
+     m_mpRecvState = MP_ADDR;
+     sFlow->RxSeqNumber ++;
+     sFlow->highestAck++;
+ 
+     action = NO_ACT;
+     if (m_mpSendState!=MP_ADDR)
+     {
+         AdvertiseAvailableAddresses(); // this is what the receiver has to do
+     }
+     else if (m_mpSendState==MP_ADDR)
+     {
+         sFlow->highestAck++; // we add 2 to highestAck because ACK, ADDR segments send it before
+         InitiateSubflows();  // this is what the initiator has to do
+     }
+   }
+ 
+   if(TxAckOpt == true)
+   {
+       if(server == true)
+       {
+           SendAcknowledge (sFlowIdx, TcpHeader::ACK, opt1);
+       }
+       else if(client == true)
+       {
+           NewACK (sFlowIdx, mptcpHeader, opt1);
+       }
+       action = NO_ACT;
+   }else if (TxACK == true)
+   {
+ 
+ NS_LOG_INFO ( "Recv: Subflow ("<<(int) sFlowIdx <<") TxSeq (" << sFlow->TxSeqNumber <<") RxSeq (" << sFlow->RxSeqNumber <<")\n" );
+ 
+       SendEmptyPacket (sFlowIdx, TcpHeader::ACK);
+       action = NO_ACT;
+   }
+   return action;
+ }
+ 
+ OptDSACK*
+ MpTcpSocketBase::createOptDSACK (OptDataSeqMapping * optDSN)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     OptDSACK* ptrDSAK = new OptDSACK (OPT_DSACK);
+     // Add the received segment which generated the currently prepared acknowledgement
+     ptrDSAK->AddfstBlock(optDSN->dataSeqNumber, optDSN->dataSeqNumber + optDSN->dataLevelLength);
+ 
+     uint64_t upperBound = 0;
+     uint64_t lowerBound = 0;
+     if ( unOrdered.size() == 1 )
+     {
+         DSNMapping *ptr1 = (* (unOrdered.begin()));
+         lowerBound = ptr1->dataSeqNumber;
+         upperBound = ptr1->dataSeqNumber + ptr1->dataLevelLength;
+     }
+     else
+     {
+         map<uint64_t, uint32_t> blocs;
+         list<DSNMapping *>::iterator current = unOrdered.begin();
+         list<DSNMapping *>::iterator next = unOrdered.begin();
+         ++next;
+ 
+         while( next != unOrdered.end() )
+         {
+             DSNMapping *ptr1 = *current;
+             DSNMapping *ptr2 = *next;
+             uint32_t  length = 0;
+             uint64_t  dsn1   = ptr1->dataSeqNumber;
+             uint64_t  dsn2   = ptr2->dataSeqNumber;
+ 
+             if ( blocs.find ( dsn1 ) != blocs.end() )
+             {
+                 length = blocs [dsn1];
+             }
+             else
+             {
+                 length       = ptr1->dataLevelLength;
+                 blocs[dsn1]  = ptr1->dataLevelLength;
+             }
+ 
+             if ( dsn1 + length == dsn2 )
+             {
+                 blocs[dsn1] = blocs[dsn1] + ptr2->dataLevelLength;
+             }
+             else
+             {
+                 current = next;
+             }
+             ++next;
+         }
+         DSNMapping *ptr1 = (* (unOrdered.begin()));
+         lowerBound = ptr1->dataSeqNumber;
+         upperBound = ptr1->dataSeqNumber + blocs[ptr1->dataSeqNumber];
+ 
+         NS_LOG_INFO ("createOptDSACK -> blocs size = " << blocs.size() );
+     }
+     ptrDSAK->AddBlock( lowerBound, upperBound);
+     return ptrDSAK;
+ }
+ 
+ void
+ MpTcpSocketBase::ReadUnOrderedData ()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     //NS_LOG_FUNCTION (this);
+     list<DSNMapping *>::iterator current = unOrdered.begin();
+     list<DSNMapping *>::iterator next = unOrdered.begin();
+ 
+     // I changed this method, now whenever a segment is readed it get dropped from that list
+     while(next != unOrdered.end())
+     {
+         ++next;
+         DSNMapping *ptr   = *current;
+         uint32_t sFlowIdx = ptr->subflowIndex;
+         MpTcpSubFlow *sFlow = subflows[ sFlowIdx ];
+         if ( (ptr->dataSeqNumber <= nextRxSequence) && (ptr->subflowSeqNumber == sFlow->RxSeqNumber) )
+         {
+             uint32_t amount = recvingBuffer->Add (ptr->packet, ptr->dataLevelLength);
+ 
+             if(amount == 0)
+                 break; // reception buffer is full
+ 
+             sFlow->RxSeqNumber += amount;
+             sFlow->highestAck   = std::max ( sFlow->highestAck, ptr->acknowledgement - 1 );
+             nextRxSequence     += amount;
+             NS_LOG_INFO ("ReadUnOrderedData("<<unOrdered.size()<<") -> in sequence data (" << amount<<") found saved => Acknowledgement ("<<sFlow->RxSeqNumber<<") data seq ("<<ptr->dataSeqNumber<<") sent on subflow ("<< sFlowIdx<<")." );
+             /**
+              * Send an acumulative acknowledge
+              */
+             switch( m_algoPR )
+             {
+                 case Eifel:
+                     //SendAcknowledge (sFlowIdx, TcpHeader::ACK, new OptTimesTamp (OPT_TT, Simulator::Now ().GetMilliSeconds (), ((OptTimesTamp *) opt)->TSval));
+                     break;
+                 case D_SACK:
+                     // don't send an ACK for already acked segment
+                     break;
+                 default:
+                     //SendEmptyPacket (sFlowIdx, TcpHeader::ACK);
+                     break;
+             }
+             SendEmptyPacket (sFlowIdx, TcpHeader::ACK);
+             NotifyDataRecv ();
+             unOrdered.erase( current );
+         }
+         current = next;
+     }
+ }
+ 
+ uint8_t
+ MpTcpSocketBase::ProcessOption (TcpOptions *opt)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     uint8_t originalSFlow = 255;
+     if( opt != 0 ) {
+     if( opt->optName == OPT_DSACK )
+     {
+         OptDSACK * dsack = (OptDSACK *) opt;
+         // fstLeft = dsack->blocks[0];         fstRight = dsack->blocks[1];
+         uint64_t fstLeft = dsack->blocks[0], fstRight = dsack->blocks[1];
+         uint64_t sndLeft = dsack->blocks[2], sndRight = dsack->blocks[3];
+         NS_LOG_DEBUG("ProcessOption -> sndLeft ("<<sndLeft<<") sndRight ("<<sndRight<<")");
+         /**
+          * go throw each sent packet which is pending for un ACK, and check if in the received option there is a ACK at the data level
+          * we prefer to drop the packet because we will not receive ACK for it
+          */
+ 
+         for (uint8_t i = 0; i < subflows.size(); i++)
+         {
+             MpTcpSubFlow *sFlow = subflows[i];
+             list<DSNMapping *>::iterator current = sFlow->mapDSN.begin();
+             list<DSNMapping *>::iterator next    = sFlow->mapDSN.begin();
+             while( current != sFlow->mapDSN.end() )
+             {
+                 ++next;
+                 DSNMapping *ptrDSN = *current;
+                 if ( ((ptrDSN->dataSeqNumber == fstLeft) && (ptrDSN->dataSeqNumber + ptrDSN->dataLevelLength == fstRight))
+                     ||
+                      ((ptrDSN->dataSeqNumber >= sndLeft) && (ptrDSN->dataSeqNumber + ptrDSN->dataLevelLength <= sndRight)) )
+                 {
+                     NS_LOG_DEBUG("acked segment with DSACK -> subflowSeqNumber ("<<ptrDSN->subflowSeqNumber<<")");
+                     /**
+                      * increment the number of ack received for that data level sequence number
+                      */
+                     if( ackedSeg.find(ptrDSN->dataSeqNumber) != ackedSeg.end() )
+                         ackedSeg[ ptrDSN->dataSeqNumber ] = ackedSeg[ ptrDSN->dataSeqNumber ] + 1;
+                     else
+                         ackedSeg[ ptrDSN->dataSeqNumber ] = 1;
+                     /**
+                      * By checking the data level sequence number in the received TCP header option
+                      * we can deduce that the current segment was correctly received, so must be removed from DSNMapping list
+                      */
+                     /*
+                     next = sFlow->mapDSN.erase( current );
+                     delete ptrDSN;
+                     */
+                 }
+                 current = next;
+             }
+         }
+     }
+     }
+     return originalSFlow;
+ }
+ 
+ bool
+ MpTcpSocketBase::IsDuplicatedAck (uint8_t sFlowIdx, MpTcpHeader l4Header, TcpOptions *opt)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     //NS_LOG_FUNCTION (this << (int)sFlowIdx << (uint32_t) l4Header.GetAckNumber ());
+     uint32_t ack = (l4Header.GetAckNumber ()).GetValue();
+     bool duplicated = false;
+ 
+     //uint8_t originalSFlow =
+     ProcessOption (opt);
+     MpTcpSubFlow *sFlow = subflows[sFlowIdx];
+ 
+     if ( ack < sFlow->TxSeqNumber )
+     {
+         // this acknowledgment don't ack the last sent data, so check to find the duplicated
+         list<DSNMapping *>::iterator current = sFlow->mapDSN.begin();
+         list<DSNMapping *>::iterator next = sFlow->mapDSN.begin();
+         while( current != sFlow->mapDSN.end() )
+         {
+             ++next;
+             DSNMapping *ptrDSN = *current;
+ 
+             NS_LOG_LOGIC ("IsDupAck -> subflow seq n° ("<< ptrDSN->subflowSeqNumber <<") data length " << ptrDSN->dataLevelLength);
+             if ( ptrDSN->subflowSeqNumber + ptrDSN->dataLevelLength <= ack )
+             {
+                 /**
+                  * increment the number of ack received for that data level sequence number
+                  */
+                 if( ackedSeg.find(ptrDSN->dataSeqNumber) != ackedSeg.end() )
+                     ackedSeg[ ptrDSN->dataSeqNumber ] = ackedSeg[ ptrDSN->dataSeqNumber ] + 1;
+                 else
+                     ackedSeg[ ptrDSN->dataSeqNumber ] = 1;
+                 /**
+                  * this segment was correctly acked, so must be removed from DSNMapping list
+                  */
+                 /*
+                 next = sFlow->mapDSN.erase( current );
+                 delete ptrDSN;
+                 */
+             }
+             else if ( (ptrDSN->subflowSeqNumber == ack) && (ack - 1 <= sFlow->highestAck) )
+             {
+             // this may have to be retransmitted
+                 NS_LOG_INFO("IsDupAck -> duplicated ack for " << ack);
+                 duplicated = true;
+                 switch ( m_algoPR )
+                 {
+                     case Eifel:
+                         if( (ptrDSN->retransmited == true) && (ptrDSN->tsval > ((OptTimesTamp *) opt)->TSecr) )
+                         {
+                             // spurious Retransmission
+                             NS_LOG_WARN ("A Spurious Retransmission detected ->");
+ 
+                             //double rtt = sFlow->rtt->est.GetSeconds();
+                             double rtt = sFlow->rtt->GetCurrentEstimate().GetSeconds();
+                             NS_LOG_WARN (Simulator::Now().GetSeconds() <<" MpTcpSocketBase -> "<< " m_localToken "<< m_localToken<<" Subflow "<< (int)sFlowIdx <<": RTT "<< sFlow->rtt->GetCurrentEstimate().GetSeconds() <<" Moving cwnd from " << sFlow->cwnd << " to " << sFlow->savedCWND << " Throughput "<<(sFlow->cwnd * sFlow->MSS * 8)/rtt<< " GlobalThroughput "<<getGlobalThroughput());
+                             sFlow->cwnd = sFlow->savedCWND;
+                             sFlow->ssthresh = sFlow->savedSSThresh;
+                         }else
+                         {
+                             DupAck (sFlowIdx, ptrDSN);
+                         }
+                         break;
+                     case D_SACK:
+                         //if( (opt != 0) && (IsRetransmitted (((OptDSACK *) opt)->blocks[0], ((OptDSACK *) opt)->blocks[1]) == true) )
+ 
+                         if(opt != 0)
+                         {
+                             NS_LOG_DEBUG ("received ACK with DSACK option !");
+                             DupDSACK (sFlowIdx, l4Header, (OptDSACK *) opt);
+                         }else
+                         {
+                             NS_LOG_DEBUG ("received ACK without DSACK option !");
+                             DupAck (sFlowIdx, ptrDSN);
+                         }
+                         break;
+                     case F_RTO:
+                         break;
+                     case TCP_DOOR:
+                         break;
+                     case NoPR_Algo:
+                         DupAck (sFlowIdx, ptrDSN);
+                         break;
+                     default:
+                         break;
+                 }
+                 break;
+             }
+             current = next;
+         }
+         if( (m_algoPR == F_RTO) && (sFlow->phase == RTO_Recovery) )
+         {
+             sFlow->ackCount ++;
+             switch ( frtoStep )
+             {
+                 case Step_2:
+                     if ( sFlow->ackCount == 1 )
+                     {   // first acknowledgement after a RTO timeout
+                         sFlow->recover = sFlow->TxSeqNumber;
+                         if( (duplicated == true) || (ack == sFlow->recover) || (ack <= sFlow->ReTxSeqNumber) )
+                         {
+                     /**
+                      * revert to the conventional RTO recovery and continue by
+                      * retransmitting unacknowledged data in slow start.
+                      * Do not enter step 3 of this algorithm.
+                      * The SpuriousRecovery variable remains false
+                      */
+                             NS_LOG_WARN ("4th dupAck -> Fast Recovery: sending new packet in slow start");
+                             frtoStep = Step_4;
+ 
+                         }else if( (duplicated == false) && (ack < sFlow->recover) )
+                         {
+                     /**
+                      * transmit up to two new (previously unsent) segments
+                      * enter step 3 of this algorithm
+                      */
+                             frtoStep = Step_3;
+                             if( (sendingBuffer->Empty() == true) || (std::min (AvailableWindow (sFlowIdx), sendingBuffer->PendingData()) == 0) )
+                             {
+                                 frtoStep = Step_4;
+                             }
+                         }
+                     }else
+                     {
+                         frtoStep = Step_4;
+                     }
+                     break;
+ 
+                 case Step_3:
+                     if(sFlow->ackCount == 2)
+                     {   // second acknowledgement after a RTO timeout
+                         if( duplicated == true )
+                         {
+                             sFlow->cwnd = 3;
+                             frtoStep = Step_4;
+                         }else if( ack > sFlow->highestAck + 1 )
+                         {
+                             sFlow->SpuriousRecovery = true;
+                             sFlow->recover = sFlow->TxSeqNumber;
+                             NS_LOG_WARN ("F-RTO -> A spurious timeout have been detected !");
+                         }
+                     }else
+                     {
+                         frtoStep = Step_4;
+                     }
+                     break;
+ 
+                 default:
+                     break;
+             }
+ 
+         }
+     }
+     return duplicated;
+ }
+ 
+ void
+ MpTcpSocketBase::DupDSACK (uint8_t sFlowIdx, MpTcpHeader mptcpHeader, OptDSACK *dsack)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     uint64_t leftEdge  = dsack->blocks[0];
+     //uint64_t rightEdge = dsack->blocks[1];
+     NS_LOG_DEBUG("ackedSeg size = "<<ackedSeg.size());
+     MpTcpSubFlow *originalSFlow = subflows[sFlowIdx];
+     DSNMapping *notAckedPkt = 0;
+     for (uint8_t i = 0; i < subflows.size(); i++)
+     {
+         MpTcpSubFlow *sFlow = subflows[i];
+         list<DSNMapping *>::iterator current = sFlow->mapDSN.begin();
+         list<DSNMapping *>::iterator next    = sFlow->mapDSN.begin();
+ 
+         while( current != sFlow->mapDSN.end() )
+         {
+             ++next;
+             DSNMapping *ptrDSN = *current;
+ 
+                 NS_LOG_DEBUG("ptrDSN->subflowSeqNumber ("<<ptrDSN->subflowSeqNumber<<") sFlow->highestAck ("<<sFlow->highestAck<<")");
+             if ( (ackedSeg.find(ptrDSN->dataSeqNumber) == ackedSeg.end()) && (ptrDSN->subflowSeqNumber == sFlow->highestAck + 1) )
+             {
+                 NS_LOG_DEBUG("updating notAckedPkt");
+                 // that's the first segment not already acked (by DSACK) in the current subflow
+                 if (notAckedPkt == 0)
+                 {
+                     notAckedPkt = ptrDSN;
+                     originalSFlow  = sFlow;
+                 }else if(notAckedPkt->dataSeqNumber > ptrDSN->dataSeqNumber)
+                 {
+                     if(lastRetransmit == 0)
+                     {
+                         lastRetransmit = ptrDSN;
+                         notAckedPkt    = ptrDSN;
+                         originalSFlow  = sFlow;
+                     }else if(lastRetransmit->dataSeqNumber < ptrDSN->dataSeqNumber)
+                     {
+                         lastRetransmit = ptrDSN;
+                         notAckedPkt    = ptrDSN;
+                         originalSFlow  = sFlow;
+                     }
+                 }
+             }
+             current = next;
+         }
+     }
+ 
+     if( (retransSeg.find(leftEdge) != retransSeg.end()) && (ackedSeg.find(leftEdge) != ackedSeg.end()) && (ackedSeg[leftEdge] > 1) )
+     {
+                                 /**
+                                  * if the segment reported in DSACK has been retransmitted and it's acked more than once (duplicated)
+                                  * spurious congestion is detected, set the variables needed to a slow start
+                                  */
+         originalSFlow->phase = DSACK_SS;
+         NS_LOG_WARN ("A Spurious Retransmission detected => trigger a slow start to the previous saved cwnd value!");
+     }else
+     {
+         if(notAckedPkt != 0)
+             DupAck (originalSFlow->routeId, notAckedPkt);
+     }
+ }
+ 
+ void
+ MpTcpSocketBase::DupAck (uint8_t sFlowIdx, DSNMapping * ptrDSN)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     MpTcpSubFlow *sFlow = subflows[ sFlowIdx ];
+     ptrDSN->dupAckCount++;
+     if ( ptrDSN->dupAckCount == 3 )
+     {
+         NS_LOG_WARN (Simulator::Now().GetSeconds() <<" DupAck -> Subflow ("<< (int)sFlowIdx <<") 3rd duplicated ACK for segment ("<<ptrDSN->subflowSeqNumber<<")");
+ 
+         sFlow->rtt->pktRetransmit (SequenceNumber32(ptrDSN->subflowSeqNumber)); // notify the RTT
+         //sFlow->rtt->SentSeq (ptrDSN->subflowSeqNumber, ptrDSN->dataLevelLength);
+ 
+         reduceCWND (sFlowIdx);
+         SetReTxTimeout (sFlowIdx); // reset RTO
+ 
+         // ptrDSN->dupAckCount   = 0;
+         // we retransmit only one lost pkt
+         Ptr<Packet> pkt = new Packet (ptrDSN->packet, ptrDSN->dataLevelLength);
+         MpTcpHeader header;
+         header.SetSourcePort      (sFlow->sPort);
+         header.SetDestinationPort (sFlow->dPort);
+         header.SetFlags           (TcpHeader::ACK);
+         header.SetSequenceNumber  (SequenceNumber32(ptrDSN->subflowSeqNumber));
+         header.SetAckNumber       (SequenceNumber32(sFlow->RxSeqNumber));       // for the acknowledgement, we ack the sFlow last received data
+         header.SetWindowSize      (AdvertisedWindowSize());
+         // save the seq number of the sent data
+         uint8_t hlen = 5;
+         uint8_t olen = 15;
+         uint8_t plen = 0;
+ 
+         header.AddOptDSN (OPT_DSN, ptrDSN->dataSeqNumber, ptrDSN->dataLevelLength, ptrDSN->subflowSeqNumber);
+ 
+         NS_LOG_WARN (Simulator::Now().GetSeconds() <<" RetransmitSegment -> "<< " m_localToken "<< m_localToken<<" Subflow "<<(int) sFlowIdx<<" DataSeq "<< ptrDSN->dataSeqNumber <<" SubflowSeq " << ptrDSN->subflowSeqNumber <<" dataLength " << ptrDSN->dataLevelLength << " packet size " << pkt->GetSize() << " 3DupACK");
+ 
+         switch ( m_algoPR )
+         {
+             case Eifel:
+                 if(ptrDSN->retransmited == false)
+                 {
+                     ptrDSN->retransmited = true;
+                     ptrDSN->tsval = Simulator::Now ().GetMilliSeconds (); // update timestamp value to the current time
+                 }
+                 header.AddOptTT  (OPT_TT, ptrDSN->tsval, 0);
+                 olen += 17;
+                 break;
+             case D_SACK:
+                 if(ptrDSN->retransmited == false)
+                 {
+                     ptrDSN->retransmited = true;
+                     retransSeg[ptrDSN->dataSeqNumber] = ptrDSN->dataLevelLength;
+                 }
+                 break;
+             default:
+                 break;
+         }
+ 
+         plen = (4 - (olen % 4)) % 4;
+         olen = (olen + plen) / 4;
+         hlen += olen;
+         header.SetLength(hlen);
+         header.SetOptionsLength(olen);
+         header.SetPaddingLength(plen);
+         m_mptcp->SendPacket (pkt, header, sFlow->sAddr, sFlow->dAddr);
+         // Notify the application of the data being sent
+ 
+     }else if ( ptrDSN->dupAckCount > 3 )
+     {
+     }
+     NS_LOG_LOGIC ("leaving DupAck");
+ }
+ 
+ void
+ MpTcpSocketBase::GenerateRTTPlot ()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     //NS_LOG_FUNCTION_NOARGS ();
+ 
+     if ( subflows[0]->measuredRTT.size() == 0)
+         return;
+ 
+     std::ofstream outfile ("rtt-cdf.plt");
+ 
+     Gnuplot rttGraph = Gnuplot ("rtt-cdf.png", "RTT Cumulative Distribution Function");
+     rttGraph.SetLegend("RTT (s)", "CDF");
+     rttGraph.SetTerminal ("png");//postscript eps color enh \"Times-BoldItalic\"");
+     rttGraph.SetExtra  ("set yrange [0:1.5]");
+ 
+     for(uint16_t idx = 0; idx < subflows.size(); idx++)
+     {
+         MpTcpSubFlow * sFlow = subflows[idx];
+         Time rtt = sFlow->rtt->GetCurrentEstimate ();
+         NS_LOG_LOGIC("saddr = " << sFlow->sAddr << ", dAddr = " << sFlow->dAddr);
+         double cdf      = 0.0;
+         int    dupCount = 1;
+         int    totCount = sFlow->measuredRTT.size();
+ 
+         if (totCount == 0)
+             continue;
+ 
+         NS_LOG_LOGIC("Estimated RTT for subflow[ "<<idx<<" ] = " << rtt.GetMilliSeconds() << " ms");
+         Gnuplot2dDataset dataSet;
+         dataSet.SetStyle (Gnuplot2dDataset::LINES_POINTS);
+         std::stringstream title;
+         title << "Subflow " << idx;
+         dataSet.SetTitle (title.str());
+ 
+         multiset<double>::iterator it = sFlow->measuredRTT.begin();
+         //list<double>::iterator it = sFlow->measuredRTT.begin();
+         double previous = *it;
+ 
+         for (it++; it != sFlow->measuredRTT.end(); it++)
+         {
+             NS_LOG_LOGIC("MpTcpSocketBase::GenerateRTTPlot -> rtt["<<idx<<"] = "<< previous);
+             if( previous == *it )
+             {
+                 dupCount++;
+             }else
+             {
+                 cdf += (double) dupCount / (double) totCount;
+                 dataSet.Add (previous, cdf);
+                 dupCount = 1;
+                 previous = *it;
+             }
+         }
+         cdf += (double) dupCount / (double) totCount;
+         dataSet.Add (previous, cdf);
+ 
+         rttGraph.AddDataset (dataSet);
+     }
+     //rttGraph.SetTerminal ("postscript eps color enh \"Times-BoldItalic\"");
+     rttGraph.GenerateOutput (outfile);
+     outfile.close();
+ }
+ 
+ bool
+ MpTcpSocketBase::StoreUnOrderedData (DSNMapping *ptr1)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     //NS_LOG_FUNCTION (this);
+     /**
+     * return the statement depending on successfully inserting or not the data
+     * if unOrdered buffer can't hold the out of sequence data and currently received
+     */
+     bool inserted = false;
+     for(list<DSNMapping *>::iterator it = unOrdered.begin(); it != unOrdered.end(); ++it)
+     {
+         DSNMapping *ptr2 = *it;
+         if(ptr1->dataSeqNumber == ptr2->dataSeqNumber)
+         {
+             NS_LOG_INFO ("Data Sequence ("<< ptr1->dataSeqNumber <<") already stored in unOrdered buffer !");
+             return false;
+         }
+         if(ptr1->dataSeqNumber < ptr2->dataSeqNumber)
+         {
+             unOrdered.insert(it, ptr1);
+             inserted = true;
+             break;
+         }
+     }
+     if ( !inserted )
+         unOrdered.insert (unOrdered.end(), ptr1);
+ 
+     return true;
+ }
+ 
+ int
+ MpTcpSocketBase::Close (void)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+   NS_LOG_LOGIC("MpTcpSocketBase" << m_node->GetId() << "::Close() -> Number of subflows = " << subflows.size());
+   // First we check to see if there is any unread rx data
+   // Bug number 426 claims we should send reset in this case.
+ 
+     GenerateRTTPlot();
+ 
+     NS_LOG_INFO("///////////////////////////////////////////////////////////////////////////////");
+     NS_LOG_INFO("Closing subflows");
+     for(uint16_t idx = 0; idx < subflows.size(); idx++)
+     {
+         if( subflows[idx]->state != CLOSED )
+         {
+             NS_LOG_INFO("Subflow " << idx);
+             NS_LOG_INFO("TxSeqNumber = " << subflows[idx]->TxSeqNumber);
+             NS_LOG_INFO("RxSeqNumber = " << subflows[idx]->RxSeqNumber);
+             NS_LOG_INFO("highestAck  = " << subflows[idx]->highestAck);
+             NS_LOG_INFO("maxSeqNb    = " << subflows[idx]->maxSeqNb);
+             ProcessAction (idx, ProcessEvent (idx, APP_CLOSE) );
+         }
+     }
+     NS_LOG_INFO("///////////////////////////////////////////////////////////////////////////////");
+   return 0;
+ }
+ 
+ bool
+ MpTcpSocketBase::CloseMultipathConnection ()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     bool closed  = false;
+     uint32_t cpt = 0;
+     for(uint32_t i = 0; i < subflows.size(); i++)
+     {
+         NS_LOG_LOGIC("Subflow (" << i << ") TxSeqNumber (" << subflows[i]->TxSeqNumber << ") RxSeqNumber = " << subflows[i]->RxSeqNumber);
+         NS_LOG_LOGIC("highestAck (" << subflows[i]->highestAck << ") maxSeqNb    = " << subflows[i]->maxSeqNb);
+ 
+         if( subflows[i]->state == CLOSED )
+             cpt++;
+     }
+     if( cpt == subflows.size() )
+         NotifyNormalClose();
+     return closed;
+ }
+ 
+ bool
+ MpTcpSocketBase::isMultipath ()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     return m_mpEnabled;
+ }
+ 
+ void
+ MpTcpSocketBase::AdvertiseAvailableAddresses ()
+ {
+ 
+     NS_LOG_FUNCTION_NOARGS();
+   if(m_mpEnabled == true)
+   {
+     // there is at least one subflow
+     MpTcpSubFlow * sFlow = subflows[0];
+     m_mpSendState = MP_ADDR;
+     MpTcpAddressInfo * addrInfo;
+     Ptr<Packet> pkt = new Packet(0);//Create<Packet> ();
+     MpTcpHeader header;
+     header.SetFlags           (TcpHeader::ACK);//flags);
+     header.SetSequenceNumber  (SequenceNumber32(sFlow->TxSeqNumber));
+     header.SetAckNumber       (SequenceNumber32(sFlow->RxSeqNumber));
+     header.SetSourcePort      (m_endPoint->GetLocalPort ());
+     header.SetDestinationPort (m_remotePort);
+ 
+     uint8_t hlen = 0;
+     uint8_t olen = 0;
+ 
+     Ptr<Ipv4L3Protocol> ipv4 = m_node->GetObject<Ipv4L3Protocol> ();
+ 
+     for(uint32_t i = 0; i < ipv4->GetNInterfaces(); i++)
+     {
+         //Ptr<NetDevice> device = m_node->GetDevice(i);
+         Ptr<Ipv4Interface> interface = ipv4->GetInterface(i);
+         Ipv4InterfaceAddress interfaceAddr = interface->GetAddress (0);
+         // do not consider loopback addresses
+         if(interfaceAddr.GetLocal() == Ipv4Address::GetLoopback())
+             continue;
+ 
+         addrInfo = new MpTcpAddressInfo();
+         addrInfo->addrID   = i;
+         addrInfo->ipv4Addr = interfaceAddr.GetLocal();
+         addrInfo->mask     = interfaceAddr.GetMask ();
+ 
+         //addrInfo->ipv4Addr = Ipv4Address::ConvertFrom(device->GetAddress());
+ //NS_LOG_INFO("MpTcpSocketBase::AdvertiseAvailableAddresses -> Ipv4 addresse = "<< addrInfo->ipv4Addr);
+ 
+         header.AddOptADDR(OPT_ADDR, addrInfo->addrID, addrInfo->ipv4Addr);
+         olen += 6;
+         localAddrs.insert(localAddrs.end(), addrInfo);
+     }
+     uint8_t plen = (4 - (olen % 4)) % 4;
+ //NS_LOG_INFO("MpTcpSocketBase::AdvertiseAvailableAddresses -> number of addresses " << localAddrs.size());
+     header.SetWindowSize (AdvertisedWindowSize());
+     // urgent pointer
+     // check sum filed
+     olen = (olen + plen) / 4;
+     hlen = 5 + olen;
+     header.SetLength(hlen);
+     header.SetOptionsLength(olen);
+     header.SetPaddingLength(plen);
+ 
+     //SetReTxTimeout (0);
+ 
+     m_mptcp->SendPacket (pkt, header, m_endPoint->GetLocalAddress (), m_remoteAddress);
+     sFlow->TxSeqNumber ++;
+     sFlow->maxSeqNb++;
+   }
+ }
+ 
+ uint32_t
+ MpTcpSocketBase::GetOutputInf (Ipv4Address addr)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     uint32_t oif = 0;
+     Ptr<Ipv4L3Protocol> ipv4 = m_node->GetObject<Ipv4L3Protocol> ();
+     for(uint32_t i = 0; i < localAddrs.size(); i++)
+     {
+         MpTcpAddressInfo* inf = localAddrs[i];
+ 
+         if(addr == inf->ipv4Addr)
+         {
+             oif = inf->addrID;
+             break;
+         }
+     }
+ 
+     return oif;
+ }
+ 
+ bool
+ MpTcpSocketBase::IsThereRoute (Ipv4Address src, Ipv4Address dst)
+ {
+   //NS_LOG_FUNCTION_NOARGS ();
+   NS_LOG_FUNCTION(this << src << dst);
+   bool found = false;
+   uint32_t interface=0;
+   // Look up the source address
+   Ptr<Ipv4> ipv4 = m_node->GetObject<Ipv4> ();
+ 
+   NS_ASSERT (ipv4->GetRoutingProtocol () != 0); //Pablo UC
+ 
+   Ipv4Header l3Header;
+   Socket::SocketErrno errno_;
+   Ptr<Ipv4Route> route;
+ 
+ 
+   interface=ipv4->GetInterfaceForAddress(src);      //Pablo UC
+   Ptr<NetDevice> oif=ipv4->GetNetDevice(interface); //Pablo UC
+                               //Pablo UC
+ 
+ 
+ //        Ptr<NetDevice> oif;
+ //        oif->SetIfIndex(GetOutputInf (src)); //specify non-zero if bound to a source address
+         //uint32_t temp=GetOutputInf(src);
+         //Ptr<NetDevice> oif(0);
+         //if (temp==0)
+         //{
+         //}else
+         	//NS_LOG_UNCOND("oif distinto de cero");
+ //        Ptr<NetDevice> temp = CreateObject <NetDevice> ();
+ 
+ 
+   l3Header.SetSource (src);
+   l3Header.SetDestination (dst);
+   route = ipv4->GetRoutingProtocol ()->RouteOutput (Ptr<Packet> (), l3Header, oif, errno_);
+ 
+   if ((route != 0) && (src == route->GetSource ()))
+   {
+     NS_LOG_INFO ("IsThereRoute -> Route from srcAddr "<< src << " to dstAddr " << dst << " oit "<<oif<<", exist !");
+     found = true;
+   }else
+     NS_LOG_INFO ("IsThereRoute -> No Route from srcAddr "<< src << " to dstAddr " << dst << " oit "<<oif<<", exist !");
+ 
+   return found;
+ }
+ 
+ bool
+ MpTcpSocketBase::IsLocalAddress (Ipv4Address addr)
+ {
+     NS_LOG_FUNCTION(this << addr);
+     bool found = false;
+     MpTcpAddressInfo * pAddrInfo;
+     for(uint32_t i = 0; i < localAddrs.size(); i++)
+     {
+         pAddrInfo = localAddrs[i];
+         if( pAddrInfo->ipv4Addr == addr)
+         {
+             found = true;
+             break;
+         }
+     }
+     return found;
+ }
+ 
+ void
+ MpTcpSocketBase::DetectLocalAddresses ()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     MpTcpAddressInfo * addrInfo;
+     Ptr<Ipv4L3Protocol> ipv4 = m_node->GetObject<Ipv4L3Protocol> ();
+ 
+     for(uint32_t i = 0; i < ipv4->GetNInterfaces(); i++)
+     {
+         //Ptr<NetDevice> device = m_node->GetDevice(i);
+         Ptr<Ipv4Interface> interface = ipv4->GetInterface(i);
+         Ipv4InterfaceAddress interfaceAddr = interface->GetAddress (0);
+         // do not consider loopback addresses
+         if( (interfaceAddr.GetLocal() == Ipv4Address::GetLoopback()) || (IsLocalAddress(interfaceAddr.GetLocal())) )
+             continue;
+ 
+         addrInfo = new MpTcpAddressInfo();
+         addrInfo->addrID   = i;
+         addrInfo->ipv4Addr = interfaceAddr.GetLocal();
+         addrInfo->mask     = interfaceAddr.GetMask ();
+ 
+         localAddrs.insert(localAddrs.end(), addrInfo);
+     }
+ }
+ 
+ uint32_t
+ MpTcpSocketBase::BytesInFlight ()
+ {
+ 
+   NS_LOG_FUNCTION_NOARGS ();
+   return unAckedDataCount; //m_highTxMark - m_highestRxAck;
+ }
+ 
+ uint16_t
+ MpTcpSocketBase::AdvertisedWindowSize ()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     uint16_t window = 0;
+ /*
+     if( recvingBuffer != 0 )
+         window = recvingBuffer->FreeSpaceSize ();
+ */
+     window = 65535;
+     return window;
+ }
+ 
+ uint32_t
+ MpTcpSocketBase::AvailableWindow (uint8_t sFlowIdx)
+ {
+   NS_LOG_FUNCTION_NOARGS ();
+   MpTcpSubFlow * sFlow = subflows[sFlowIdx];
+   uint32_t window   = std::min ( remoteRecvWnd, static_cast<uint32_t> (sFlow->cwnd) ) * sFlow->MSS;
+   uint32_t unAcked  = sFlow->maxSeqNb - sFlow->highestAck;
+   NS_LOG_LOGIC("Subflow ("<< (int)sFlowIdx <<"): AvailableWindow -> remoteRecvWnd  = " << remoteRecvWnd <<" unAckedDataCnt = " << unAcked <<" CWND in bytes  = " << sFlow->cwnd * sFlow->MSS);
+   if (window < unAcked) //DataCount)
+   {
+       NS_LOG_LOGIC("MpTcpSocketBase::AvailableWindow -> Available Tx window is 0");
+       return 0;  // No space available
+   }
+   return (window - unAcked);//DataCount);       // Amount of window space available
+ }
+ 
+ uint32_t
+ MpTcpSocketBase::GetTxAvailable ()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     //NS_LOG_INFO ("sendingBuffer->FreeSpaceSize () == " << sendingBuffer->FreeSpaceSize ());
+     return sendingBuffer->FreeSpaceSize ();
+ }
+ 
+ void
+ MpTcpSocketBase::SetSourceAddress (Ipv4Address src)
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     m_localAddress = src;
+     if(m_endPoint != 0)
+     {
+         m_endPoint->SetLocalAddress(src);
+     }
+ }
+ 
+ Ipv4Address
+ MpTcpSocketBase::GetSourceAddress ()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     return m_localAddress;
+ }
+ 
+ uint8_t
+ MpTcpSocketBase::LookupByAddrs (Ipv4Address src, Ipv4Address dst)
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     MpTcpSubFlow *sFlow = 0;
+     uint8_t sFlowIdx = m_maxSubFlowNumber;
+ 
+     if( IsThereRoute (src, dst)==false )
+     {
+         // there is problem in the stated src (local) address
+         for(vector<MpTcpAddressInfo *>::iterator it=localAddrs.begin(); it!=localAddrs.end(); ++it)
+         {
+             Ipv4Address ipv4Addr = (*it)->ipv4Addr;
+             if( IsThereRoute (ipv4Addr, dst)==true )
+             {
+                 src = ipv4Addr;
+                 m_localAddress  = ipv4Addr;
+                 break;
+             }
+         }
+     }
+ 
+     for(uint8_t i = 0; i < subflows.size(); i++)
+     {
+         sFlow = subflows[i];
+         // on address can only participate to a one subflow, so we can find that subflow by unsing the source address or the destination, but the destination address is the correct one, so use it
+         if( (sFlow->sAddr==src && sFlow->dAddr==dst) || (sFlow->dAddr==dst) )
+         {
+             sFlowIdx = i;
+             break;
+         }
+     }
+ 
+     if(! (sFlowIdx < m_maxSubFlowNumber) )
+     {
+       if(m_connected == false && subflows.size()==1)
+       {
+           sFlowIdx = 0;
+       }
+       else
+       {
+           if( IsLocalAddress(m_localAddress) )
+           {
+                 sFlowIdx = subflows.size();
+                 MpTcpSubFlow *sFlow = new MpTcpSubFlow( sfInitSeqNb[m_localAddress] + 1);
+                 sFlow->routeId   = subflows[subflows.size() - 1]->routeId + 1;
+                 sFlow->dAddr     = m_remoteAddress;
+                 sFlow->dPort     = m_remotePort;
+                 sFlow->sAddr     = m_localAddress;
+                 sFlow->sPort     = m_localPort;
+                 sFlow->MSS       = getL3MTU(m_localAddress);
+                 sFlow->bandwidth = getBandwidth(m_endPoint->GetLocalAddress ());
+                 // at its creation, the subflow take the state of the global connection
+                 if(m_state == LISTEN)
+                     sFlow->state = m_state;
+                 else if(m_state == ESTABLISHED)
+                     sFlow->state = SYN_SENT;
+                 subflows.insert(subflows.end(), sFlow);
+                 NS_LOG_INFO("Node ("<<m_node->GetId()<<") LookupByAddrs -> sFlowIdx " << (int) sFlowIdx <<" created: (src,dst) = (" << sFlow->sAddr << "," << sFlow->dAddr << ")" );
+           }else
+           {
+                 NS_LOG_WARN ("MpTcpSocketBase::LookupByAddrs -> sub flow related to (src,dst) = ("<<m_endPoint->GetLocalAddress()<<","<<m_endPoint->GetPeerAddress()<<") not found !");
+           }
+       }
+     }
+ 
+     NS_LOG_INFO("Node ("<<m_node->GetId()<<") LookupByAddrs -> subflows number = " << subflows.size() <<" (src,dst) = (" << src << "," << dst << ") below to subflow " << (int) sFlowIdx );
+ 
+     return sFlowIdx;
+ }
+ 
+ void
+ MpTcpSocketBase::OpenCWND (uint8_t sFlowIdx, uint32_t ackedBytes)
+ {
+     NS_LOG_FUNCTION(this << (int) sFlowIdx << ackedBytes);
+     MpTcpSubFlow * sFlow = subflows[sFlowIdx];
+     double   increment = 0;
+     double   cwnd      = sFlow->cwnd;
+     uint32_t ssthresh  = sFlow->ssthresh;
+     uint32_t segSize   = sFlow->MSS;
+     bool     normalCC  = true;
+ 
+     if ( sFlow->phase == DSACK_SS )
+     {
+ 
+         if( cwnd + 1 < sFlow->savedCWND )
+         {
+             increment = 1;
+             normalCC  = false;
+             NS_LOG_WARN ("Subflow ("<< (int) sFlowIdx <<") Congestion Control (DSACK Slow Start) increment is 1 to reach "<< sFlow->savedCWND );
+         }else
+         {
+             NS_LOG_WARN ("End of DSACK phase in subflow ("<< (int) sFlowIdx <<") Congestion Control (DSACK Slow Start) reached "<< sFlow->savedCWND );
+             sFlow->savedCWND = 0;
+             sFlow->phase = Congestion_Avoidance;
+         }
+     }else if( (sFlow->phase == RTO_Recovery) && (cwnd * segSize < ssthresh) )
+     {
+         increment = 1;
+         normalCC  = false;
+         NS_LOG_WARN (Simulator::Now().GetSeconds() <<" Subflow ("<< (int) sFlowIdx <<") Congestion Control (Slow Start Recovery) increment is 1 current cwnd "<< cwnd );
+     }
+     if (normalCC == true)
+     {
+     if( cwnd * segSize < ssthresh )
+     {
+         increment = 1;
+         NS_LOG_ERROR ("Congestion Control (Slow Start) increment is 1");
+     }else if( totalCwnd != 0 )
+     {
+         switch ( m_algoCC )
+         {
+             case RTT_Compensator:
+                 //increment = std::min( alpha * ackedBytes / totalCwnd, (double) ackedBytes / cwnd );
+                 calculateSmoothedCWND (sFlowIdx);
+                 calculate_alpha();
+                 increment = std::min( alpha / totalCwnd, 1.0 / cwnd );
+                 NS_LOG_ERROR ("Congestion Control (RTT_Compensator): alpha "<<alpha<<" ackedBytes (" << ackedBytes << ") totalCwnd ("<< totalCwnd<<") -> increment is "<<increment);
+                 break;
+ 
+             case Linked_Increases:
+                 calculateSmoothedCWND (sFlowIdx);
+                 calculate_alpha();
+                 increment = alpha / totalCwnd;
+                 NS_LOG_ERROR ("Subflow "<<(int)sFlowIdx<<" Congestion Control (Linked_Increases): alpha "<<alpha<<" increment is "<<increment<<" ssthresh "<< ssthresh << " cwnd "<<cwnd );
+                 break;
+ 
+             case Uncoupled_TCPs:
+                 increment = 1.0 / cwnd;
+                 NS_LOG_ERROR ("Subflow "<<(int)sFlowIdx<<" Congestion Control (Uncoupled_TCPs) increment is "<<increment<<" ssthresh "<< ssthresh << " cwnd "<<cwnd);
+                 break;
+ 
+             case Fully_Coupled :
+                 increment = 1.0 / totalCwnd;
+                 NS_LOG_ERROR ("Subflow "<<(int)sFlowIdx<<" Congestion Control (Fully_Coupled) increment is "<<increment<<" ssthresh "<< ssthresh << " cwnd "<<cwnd);
+                 break;
+ 
+             default :
+                 increment = 1.0 / cwnd;
+                 break;
+         }
+     }else
+     {
+         increment = 1 / cwnd;
+         NS_LOG_ERROR ("Congestion Control (totalCwnd == 0) increment is "<<increment);
+     }
+     }
+     if (totalCwnd + increment <= remoteRecvWnd)
+         sFlow->cwnd += increment;
+     double rtt = sFlow->rtt->GetCurrentEstimate().GetSeconds();
+     NS_LOG_WARN (Simulator::Now().GetSeconds() <<" MpTcpSocketBase -> "<< " m_localToken "
+     		<< m_localToken<<" Subflow "<< (int)sFlowIdx <<": RTT "<< sFlow->rtt->GetCurrentEstimate().GetSeconds()
+     		<<" Moving cwnd from " << cwnd << " to " << sFlow->cwnd <<" Throughput "<<(sFlow->cwnd * sFlow->MSS * 8)/rtt
+     		<< " GlobalThroughput "<<getGlobalThroughput()<< " Efficacity " <<  getConnectionEfficiency() << " delay "
+     		<<getPathDelay(sFlowIdx)<<" alpha "<< alpha <<" Sum CWND ("<< totalCwnd <<")");
+ }
+ 
+ void
+ MpTcpSocketBase::calculate_alpha ()
+ {
+     // this method is called whenever a congestion happen in order to regulate the agressivety of subflows
+    NS_LOG_FUNCTION_NOARGS ();
+    meanTotalCwnd = totalCwnd = alpha = 0;
+    double maxi       = 0;
+    double sumi       = 0;
+ 
+    for (uint32_t i = 0; i < subflows.size() ; i++)
+    {
+        MpTcpSubFlow * sFlow = subflows[i];
+ 
+        totalCwnd += sFlow->cwnd;
+        meanTotalCwnd += sFlow->scwnd;
+ 
+      /* use smmothed RTT */
+      Time time = sFlow->rtt->GetCurrentEstimate ();
+      double rtt = time.GetSeconds ();
+      if (rtt < 0.000001)
+        continue;                 // too small
+ 
+      double tmpi = sFlow->scwnd / (rtt * rtt);
+      if (maxi < tmpi)
+        maxi = tmpi;
+ 
+      sumi += sFlow->scwnd / rtt;
+    }
+    if (!sumi)
+      return;
+    alpha = meanTotalCwnd * maxi / (sumi * sumi);
+    NS_LOG_ERROR ("calculate_alpha: alpha "<<alpha<<" totalCwnd ("<< meanTotalCwnd<<")");
+ }
+ 
+ void
+ MpTcpSocketBase::calculateSmoothedCWND (uint8_t sFlowIdx)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     MpTcpSubFlow *sFlow = subflows [sFlowIdx];
+     if (sFlow->scwnd < 1)
+         sFlow->scwnd = sFlow->cwnd;
+     else
+         sFlow->scwnd = sFlow->scwnd * 0.875 + sFlow->cwnd * 0.125;
+ }
+ 
+ void
+ MpTcpSocketBase::Destroy (void)
+ {
+     NS_LOG_FUNCTION_NOARGS();
+ }
+ 
+ MpTcpSubFlow *
+ MpTcpSocketBase::GetSubflow (uint8_t sFlowIdx)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     return subflows [sFlowIdx];
+ }
+ 
+ void
+ MpTcpSocketBase::SetCongestionCtrlAlgo (CongestionCtrl_t ccalgo)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     m_algoCC = ccalgo;
+ }
+ 
+ void
+ MpTcpSocketBase::SetDataDistribAlgo (DataDistribAlgo_t ddalgo)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     m_distribAlgo = ddalgo;
+ }
+ 
+ bool
+ MpTcpSocketBase::rejectPacket(double threshold)
+ {
+     NS_LOG_FUNCTION_NOARGS();
+ 
+     bool reject = false;
+     double probability = (double) (rand() % 1013) / 1013.0;
+     NS_LOG_INFO("rejectPacket -> probability == " << probability);
+     if( probability < threshold )
+         reject = true;
+ 
+     return reject;
+ 
+ }
+ 
+ double
+ MpTcpSocketBase::getPathDelay(uint8_t idxPath)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     TimeValue delay;
+     Ptr<Ipv4L3Protocol> ipv4 = m_node->GetObject<Ipv4L3Protocol> ();
+     // interface 0 is the loopback interface
+     Ptr<Ipv4Interface> interface = ipv4->GetInterface(idxPath + 1);
+     Ipv4InterfaceAddress interfaceAddr = interface->GetAddress (0);
+     // do not consider loopback addresses
+     if(interfaceAddr.GetLocal() == Ipv4Address::GetLoopback())
+         return 0.0;
+     Ptr<NetDevice> netDev =  interface->GetDevice();
+     Ptr<Channel> P2Plink  =  netDev->GetChannel();
+     Ptr<PointToPointChannel> temp = CreateObject <PointToPointChannel> ();
+ 
+     if (P2Plink->GetInstanceTypeId() ==  temp->GetInstanceTypeId())
+     	P2Plink->GetAttribute(string("Delay"), delay);
+     else
+     	delay=Time(0);
+     return delay.Get().GetSeconds();
+ }
+ 
+ uint64_t
+ MpTcpSocketBase::getPathBandwidth(uint8_t idxPath)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     StringValue str;
+     Ptr<Ipv4L3Protocol> ipv4 = m_node->GetObject<Ipv4L3Protocol> ();
+     // interface 0 is the loopback interface
+     Ptr<Ipv4Interface> interface = ipv4->GetInterface(idxPath + 1);
+     Ipv4InterfaceAddress interfaceAddr = interface->GetAddress (0);
+     // do not consider loopback addresses
+     if(interfaceAddr.GetLocal() == Ipv4Address::GetLoopback())
+         return 0.0;
+     Ptr<NetDevice> netDev =  interface->GetDevice();
+ 
+     if( netDev->IsPointToPoint() == true )
+     {
+        netDev->GetAttribute(string("DataRate"), str);
+     }else
+     {
+         //Ptr<Channel> link  =  netDev->GetChannel();
+         //link->GetAttribute(string("DataRate"), str);
+         str=string("0");
+     }
+ 
+     DataRate bandwidth (str.Get());
+     return bandwidth.GetBitRate ();
+ }
+ 
+ double
+ MpTcpSocketBase::getGlobalThroughput()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     double gThroughput = 0;
+     for(uint32_t i=0; i< subflows.size(); i++)
+     {
+         MpTcpSubFlow* sFlow = subflows[i];
+         gThroughput += (sFlow->cwnd * sFlow->MSS * 8) / sFlow->rtt->GetCurrentEstimate().GetSeconds();
+     }
+     return gThroughput;
+ }
+ 
+ double
+ MpTcpSocketBase::getConnectionEfficiency()
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     double gThroughput =0.0;
+     uint64_t gBandwidth = 0;
+     for(uint32_t i = 0; i < subflows.size(); i++)
+     {
+         MpTcpSubFlow* sFlow = subflows[i];
+         gThroughput += (sFlow->cwnd * sFlow->MSS * 8) / sFlow->rtt->GetCurrentEstimate().GetSeconds();
+ 
+         gBandwidth += getPathBandwidth(i);
+     }
+     return gThroughput / gBandwidth;
+ }
+ 
+ DSNMapping*
+ MpTcpSocketBase::getAckedSegment(uint64_t lEdge, uint64_t rEdge)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+     for(uint8_t i = 0; i < subflows.size(); i++)
+     {
+         MpTcpSubFlow* sFlow = subflows[i];
+         for (list<DSNMapping *>::iterator it = sFlow->mapDSN.begin(); it != sFlow->mapDSN.end(); ++it)
+         {
+             DSNMapping* dsn = *it;
+             if(dsn->dataSeqNumber == lEdge && dsn->dataSeqNumber + dsn->dataLevelLength == rEdge)
+             {
+                 return dsn;
+             }
+         }
+     }
+     return 0;
+ }
+ 
+ //Clases Añadidas por ser Virtuales en tcp-socket-base
+ 
+ Ptr<TcpSocketBase> MpTcpSocketBase::Fork (void)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+ 
+   return CopyObject<MpTcpSocketBase> (this);
+ }
+ 
+ void MpTcpSocketBase::SetSSThresh (uint32_t threshold)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+   m_ssThresh = threshold;
+ }
+ 
+ uint32_t MpTcpSocketBase::GetSSThresh (void) const
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+   return m_ssThresh;
+ }
+ 
+ void
+ MpTcpSocketBase::SetInitialCwnd (uint32_t cwnd)
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+   NS_ABORT_MSG_UNLESS (m_state == CLOSED, "TcpNewReno::SetInitialCwnd() cannot change initial cwnd after connection started.");
+   m_initialCWnd = cwnd;
+ }
+ 
+ uint32_t
+ MpTcpSocketBase::GetInitialCwnd (void) const
+ {
+ 	NS_LOG_FUNCTION_NOARGS ();
+   return m_initialCWnd;
+ }
+ 
+ 
+ 
+ /*
+ bool
+ MpTcpSocketBase::IsRetransmitted (uint64_t leftEdge, uint64_t rightEdge)
+ {
+     bool retransmitted = false;
+ 
+     for (uint8_t i = 0; i < subflows.size(); i++)
+     {
+         MpTcpSubFlow *sFlow = subflows[i];
+         list<DSNMapping *>::iterator current = sFlow->mapDSN.begin();
+         list<DSNMapping *>::iterator next = sFlow->mapDSN.begin();
+         while( current != sFlow->mapDSN.end() )
+         {
+             ++next;
+             DSNMapping *ptrDSN = *current;
+             if ( (ptrDSN->dataSeqNumber >= leftEdge) && (ptrDSN->dataSeqNumber + ptrDSN->dataLevelLength <= rightEdge) )
+             {
+                 // By checking the data level sequence number in the received TCP header option
+                 // we can find if the segment has already been retransmitted or not
+                 retransmitted = ptrDSN->retransmited;
+             }
+             if ( retransmitted == true )
+             {
+                 NS_LOG_WARN("Segement between seq n°"<< leftEdge <<" and "<< rightEdge <<" retransmitted !");
+                 break;
+             }
+             current = next;
+         }
+     }
+     return retransmitted;
+ }
+ */
+ 
+ 
+ 
+ 
+ }//namespace ns3
+ 
+ 
+ 
+ 
+ 
+ 
+ 
+ 
+ // Retransmit timeout
+ //void MpTcpSocketBase::Retransmit (void)
+ //{
+ //  NS_LOG_FUNCTION (this);
+ //  NS_LOG_LOGIC (this << " ReTxTimeout Expired at time " << Simulator::Now ().GetSeconds ());
+ //  m_inFastRec = false;
+ //
+ //  // If erroneous timeout in closed/timed-wait state, just return
+ //  if (m_state == CLOSED || m_state == TIME_WAIT) return;
+ //  // If all data are received (non-closing socket and nothing to send), just return
+ //  if (m_state <= ESTABLISHED && m_txBuffer.HeadSequence () >= m_highTxMark) return;
+ //
+ //  // According to RFC2581 sec.3.1, upon RTO, ssthresh is set to half of flight
+ //  // size and cwnd is set to 1*MSS, then the lost packet is retransmitted and
+ //  // TCP back to slow start
+ //  m_ssThresh = std::max (2 * m_segmentSize, BytesInFlight () / 2);
+ //  m_cWnd = m_segmentSize;
+ //  m_nextTxSequence = m_txBuffer.HeadSequence (); // Restart from highest Ack
+ //  NS_LOG_INFO ("RTO. Reset cwnd to " << m_cWnd <<
+ //               ", ssthresh to " << m_ssThresh << ", restart from seqnum " << m_nextTxSequence);
+ //  m_rtt->IncreaseMultiplier ();             // Double the next RTO
+ //  DoRetransmit ();                          // Retransmit the packet
+ //}
+ //
+ //
+ //void
+ //MpTcpSocketBase::InitializeCwnd (void)
+ //{
+ //  /*
+ //   * Initialize congestion window, default to 1 MSS (RFC2001, sec.1) and must
+ //   * not be larger than 2 MSS (RFC2581, sec.3.1). Both m_initiaCWnd and
+ //   * m_segmentSize are set by the attribute system in ns3::TcpSocket.
+ //   */
+ //  m_cWnd = m_initialCWnd * m_segmentSize;
+ //}
+ //
+ //} // namespace ns3
diff -crBN old/ns-3.13/src/mptcp/model/mp-tcp-socket-base.h new/ns-3.13/src/mptcp/model/mp-tcp-socket-base.h
*** old/ns-3.13/src/mptcp/model/mp-tcp-socket-base.h	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/model/mp-tcp-socket-base.h	2012-11-07 09:26:37.017498000 +0100
***************
*** 0 ****
--- 1,376 ----
+ 
+ /* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
+ /*
+  * Copyright (c) 2010 Adrian Sai-wah Tam
+  *
+  * This program is free software; you can redistribute it and/or modify
+  * it under the terms of the GNU General Public License version 2 as
+  * published by the Free Software Foundation;
+  *
+  * This program is distributed in the hope that it will be useful,
+  * but WITHOUT ANY WARRANTY; without even the implied warranty of
+  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+  * GNU General Public License for more details.
+  *
+  * You should have received a copy of the GNU General Public License
+  * along with this program; if not, write to the Free Software
+  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
+  *
+  * Author: Adrian Sai-wah Tam <adrian.sw.tam@gmail.com>
+  */
+ 
+ #ifndef MP_TCP_SOCKET_BASE_H
+ #define MP_TCP_SOCKET_BASE_H
+ 
+ #include "ns3/tcp-socket-base.h"
+ 
+ #include <stdint.h>
+ #include <queue>
+ #include "ns3/callback.h"
+ #include "ns3/traced-value.h"
+ #include "ns3/tcp-socket.h"
+ #include "ns3/ptr.h"
+ #include "ns3/ipv4-address.h"
+ #include "ns3/event-id.h"
+ #include "ns3/tcp-typedefs.h"
+ #include "ns3/pending-data.h"
+ #include "ns3/sequence-number.h"
+ #include "ns3/rtt-estimator.h"
+ #include "mp-tcp-l4-protocol.h"
+ 
+ 
+ #include "mp-tcp-typedefs.h"
+ 
+ #include <vector>
+ #include <list>
+ #include <map>
+ 
+ using namespace std;
+ 
+ namespace ns3 {
+ 
+ /**
+  * \ingroup socket
+  * \ingroup tcp
+  *
+  * \brief Implémentation de MPTCP (Multipath TCP).
+  *
+  *  Cette classe contient l'implémentation de TCP Multipath, ainsi que les interfaces permettant à l'application de dialoguer avec la couche transport (Bind, Listen, Connect, Close, etc.). Elle regroupe la liste des différents sous-flux utilisés, la fenêtre de congestion totale, etc.
+  *
+  */
+ 
+ class Ipv4EndPoint;
+ class Node;
+ class Packet;
+ 
+ class MpTcpL4Protocol;
+ 
+ 
+ class MpTcpSocketBase : public TcpSocketBase
+ {
+ public:
+ 
+   static TypeId GetTypeId (void);
+   MpTcpStateMachine *m_stateMachine;
+   /**
+    * Create an unbound tcp socket.
+    */
+   MpTcpSocketBase (void);
+   MpTcpSocketBase (Ptr<Node> node);
+   virtual ~MpTcpSocketBase (void);
+ 
+   // From TcpSocketBase
+   virtual int Connect (Address &address);
+   virtual int Connect(Ipv4Address servAddr, uint16_t servPort);
+   virtual int Close (void);
+   virtual int Bind ();
+   virtual int Bind (const Address &address);
+   virtual int Listen (void);
+ 
+   virtual uint32_t Recv (uint8_t* buf, uint32_t size);
+   virtual uint32_t AvailableWindow(uint8_t sFlowIdx);// Return unfilled portion of window
+   void     SetNode (Ptr<Node> node);
+   Ptr<Node>   GetNode ();
+   void     SetMpTcp (Ptr<MpTcpL4Protocol> mptcp);
+ 
+   bool     SendBufferedData ();
+   int      FillBuffer (uint8_t* buf, uint32_t size);
+   uint32_t GetTxAvailable();
+ 
+ 
+   uint8_t  GetMaxSubFlowNumber();
+   void     SetMaxSubFlowNumber(uint8_t num);
+   uint8_t  GetMinSubFlowNumber();
+   void     SetMinSubFlowNumber(uint8_t num);
+   bool     SetLossThreshold(uint8_t sFlowIdx, double lossThreshold);
+ 
+   void SetSourceAddress(Ipv4Address src);
+   Ipv4Address GetSourceAddress();
+ 
+   // extended Socket API for Multipath support
+   bool isMultipath();
+   void AdvertiseAvailableAddresses();
+   bool InitiateSubflows();
+ 
+   void allocateSendingBuffer(uint32_t size);
+   void allocateRecvingBuffer(uint32_t size);
+   void SetunOrdBufMaxSize(uint32_t size);
+       /**
+        * Permet de déterminer le délai sur un chemin.
+          * @param idxPath est le numéro de chemin qui correspand à une interface réseau
+          * @return le délai sur le chemin identifié par idxPath
+          */
+   double getPathDelay(uint8_t idxPath);
+       /**
+          * Permet de déterminer la bande passante d'un chemin.
+          * @param idxPath est le numéro de chemin qui correspand à une interface réseau
+          * @return la bande passante sur le chemin identifié par idxPath
+          */
+   uint64_t getPathBandwidth(uint8_t idxPath);
+   double getConnectionEfficiency();
+         /**
+          * Permet de calculer de façon aléatoire une probabilité, et de la comparer au seuil en paramètre.
+          * @param threshold est un seuil
+          * @return le résultat de comparaison
+          */
+   bool rejectPacket(double threshold);
+ 
+   MpTcpSubFlow *GetSubflow (uint8_t sFlowIdx);
+ 
+   uint32_t GetOutputInf (Ipv4Address addr);
+       /**
+       * Permet de spécifier l'algorithme à utiliser pour le controle de congestion
+       * par exemple: Fully Coupled, Linked Increases, Uncoupled TCPs, RTT Compensator.
+       * @param ccalgo algorithme de controle de congestion.
+       */
+   void SetCongestionCtrlAlgo (CongestionCtrl_t ccalgo);
+       /**
+       * Permet de spécifier l'algorithme à utiliser pour la distribution des données sur les différents chemins.
+       * par exemple: Round Robin.
+       * @param ddalgo algorithme de distribution de données.
+       */
+   void SetDataDistribAlgo    (DataDistribAlgo_t ddalgo);
+     /**
+       * Permet de spécifier l'algorithme à utiliser pour la détection et/ou la réaction au phénomène de réorganisation des paquets du au multipath.
+       * par exemple: Round Robin.
+       * @param pralgo algorithme de détection et/ou réaction à la réorganisation des paquets.
+       */
+   void SetPacketReorderAlgo  (PacketReorder_t pralgo);
+ 
+ 
+ 
+ protected:
+ 
+ 
+   /*/*////ANTIGUO/////////////////////*/*/*/*/*/
+ 
+   //virtual void DupAck (const TcpHeader& t, uint32_t count);  // Fast retransmit
+   //virtual void Retransmit (void); // Retransmit timeout
+ 
+   TracedValue<uint32_t>  m_cWnd;
+   //uint32_t               m_ssThresh;     //< Slow Start Threshold
+   //uint32_t               m_initialCWnd;  //< Initial cWnd value
+   uint32_t               m_retxThresh;   //< Fast Retransmit threshold
+   bool                   m_inFastRec;    //< currently in fast recover
+ 
+   /*/*////ANTIGUO/////////////////////*/*/*/*/*/
+ 
+ 
+   Ptr<Node>     m_node;
+   Ipv4EndPoint *m_endPoint;
+   Ptr<MpTcpL4Protocol> m_mptcp;
+   Ipv4Address   m_localAddress;
+   uint16_t      m_localPort;
+   Ipv4Address   m_remoteAddress;
+   uint16_t      m_remotePort;
+   enum Socket::SocketErrno m_errno;
+ 
+   TcpStates_t   m_state;
+   bool       m_connected; // used for listen state
+ 
+   // Multipath related variables
+   uint8_t    m_maxSubFlowNumber;
+   uint8_t    m_minSubFlowNumber;
+   uint8_t    m_subFlowNumber;
+   MpStates_t m_mpState;
+   MpStates_t m_mpSendState;
+   MpStates_t m_mpRecvState;
+   bool       m_mpEnabled;
+   bool       m_addrAdvertised;
+   vector<MpTcpSubFlow *>     subflows;
+   vector<MpTcpAddressInfo *> localAddrs;
+   vector<MpTcpAddressInfo *> remoteAddrs;
+   map<Ipv4Address, uint32_t> sfInitSeqNb;
+   list<DSNMapping *>         unOrdered;    // buffer that hold the out of sequence received packet
+   uint32_t                   unOrdMaxSize; // maximum size of the buf that hold temporary the out of sequence data
+   // add list to store received part of not lost data
+   void      GenerateRTTPlot();
+ 
+   uint8_t   m_lastUsedsFlowIdx;
+ 
+   double    totalCwnd;
+   double    meanTotalCwnd;
+   double    alpha;
+   CongestionCtrl_t  m_algoCC;         // Algorithm for Congestion Control
+   DataDistribAlgo_t m_distribAlgo;    // Algorithm for Data Distribution
+   PacketReorder_t   m_algoPR;         // Algorithm for Handling Packet Reordering
+      /**
+       * Permet de traiter les options (ex: OPT_MPC, OPT_JOIN) contenus dans le segment MPTCP.
+       * @param sFlowIdx l'identifiant du chemin
+       * @param pkt un pointeur vers le paquet
+       * @param mptcpHeader l'entete du segment MPTCP
+       * @return l'action à faire
+       */
+   Actions_t ProcessHeaderOptions(uint8_t sFlowIdx, Ptr<Packet> pkt, uint32_t *dataLen, MpTcpHeader mptcpHeader);
+   bool      StoreUnOrderedData(DSNMapping *ptr1);
+   void      ReadUnOrderedData ();
+   void      ProcessMultipathState();
+   void      OpenCWND(uint8_t sFlowIdx, uint32_t ackedBytes);
+   void      calculate_alpha ();
+   void      calculateTotalCWND ();
+   void      calculateSmoothedCWND (uint8_t sFlowIdx);
+   void      reduceCWND (uint8_t sFlowIdx);
+   DSNMapping* getAckedSegment(uint8_t sFlowIdx, uint32_t ack);
+   DSNMapping* getAckedSegment(uint64_t lEdge, uint64_t rEdge);
+   double    getGlobalThroughput();
+ 
+ 
+   uint8_t   getSubflowToUse();
+ 
+ 
+   // Multipath tockens
+   uint32_t  m_localToken;
+   uint32_t  m_remoteToken;
+ 
+ 
+   uint64_t  m_aggregatedBandwidth;
+ 
+   DataBuffer *sendingBuffer;
+   DataBuffer *recvingBuffer;
+ 
+   // Rx buffer state
+   uint32_t m_rxAvailable; // amo  unt of data available for reading through Recv
+   uint32_t m_rxBufSize;   // size in bytes of the data in the rx buf
+   // note that these two are not the same: rxAvailbale is the number of
+   // contiguous sequenced bytes that can be read, rxBufSize is the TOTAL size
+   // including out of sequence data, such that m_rxAvailable <= m_rxBufSize
+ 
+ 
+   //Funciones añadidas por ser virtuales = 0 en tcp-socket-base
+     virtual Ptr<TcpSocketBase> Fork (void); // Call CopyObject<TcpNewReno> to clone me
+     virtual void     SetSSThresh (uint32_t threshold);
+     virtual uint32_t GetSSThresh (void) const;
+     virtual void     SetInitialCwnd (uint32_t cwnd);
+     virtual uint32_t GetInitialCwnd (void) const;
+     virtual void DupAck (const TcpHeader& t, uint32_t count); // Received dupack
+ 
+ 
+ private:
+   friend class Tcp;
+     // invoked by Tcp class
+     bool      client;
+     bool      server;
+ 
+     /*/*////////////ANTIGUO////////////////////////7
+ 
+     void InitializeCwnd (void);            // set m_cWnd when connection starts
+ 
+     /*/*////////////ANTIGUO////////////////////////7
+ 
+     int       Binding ();
+     //void      ForwardUp (Ptr<Packet> p, Ipv4Address ipv4Remote, uint16_t port, Ptr<Ipv4Interface> inter);
+     void      ForwardUp (Ptr<Packet> p, Ipv4Header ipv4Head, uint16_t port, Ptr<Ipv4Interface> inter);
+     void      Destroy (void);
+ 
+     void      SendEmptyPacket (uint8_t sFlowId, uint8_t flags);
+     void      SendAcknowledge (uint8_t sFlowId, uint8_t flags, TcpOptions *opt);
+ 
+     bool      SendPendingData ();
+     bool      ProcessAction   (uint8_t sFlowIdx, Actions_t a);
+     bool      ProcessAction   (uint8_t sFlowIdx, MpTcpHeader mptcpHeader, Ptr<Packet> pkt, uint32_t dataLen, Actions_t a);
+     Actions_t ProcessEvent    (uint8_t sFlowId, Events_t e);
+       /**
+       * Au coté émetteur, permet de traiter une option reçue dans un acquittement avant de vérifier si ce dernier est dupliqué ou non.
+       * @param opt classe représentant l'option reçue
+       * @return the subflow index on which the missed segment have been originally transmitted
+       */
+     uint8_t   ProcessOption   (TcpOptions *opt);
+     void      SetReTxTimeout  (uint8_t sFlowIdx);
+     void      ReTxTimeout     (uint8_t sFlowIdx);
+     void      Retransmit      (uint8_t sFlowIdx);
+     bool      IsRetransmitted (uint64_t leftEdge, uint64_t rightEdge);
+     bool      IsDuplicatedAck (uint8_t sFlowIdx, MpTcpHeader l4Header, TcpOptions *opt);
+     void      DupDSACK (uint8_t sFlowIdx, MpTcpHeader mptcpHeader, OptDSACK *dsack);
+     void      DupAck (uint8_t sFlowIdx, DSNMapping * ptrDSN);
+     void      NewACK (uint8_t sFlowIdx, MpTcpHeader mptcpHeader, TcpOptions *opt);
+ 
+ 
+     uint8_t   LookupByAddrs   (Ipv4Address src, Ipv4Address dst);
+     void      DetectLocalAddresses();
+     uint32_t  getL3MTU        (Ipv4Address addr);
+     uint64_t  getBandwidth    (Ipv4Address addr);
+ 
+       //methods for window management
+     virtual uint32_t  BytesInFlight();  // Return total bytes in flight
+ 
+     virtual bool IsThereRoute  (Ipv4Address src, Ipv4Address dst);
+     virtual bool IsLocalAddress(Ipv4Address addr);
+ 
+     virtual bool CloseMultipathConnection();
+ 
+     //methods for Rx buffer management
+     uint16_t AdvertisedWindowSize();
+ 
+     // Window management variables
+     uint32_t                       m_rxWindowSize;         //Flow control window
+     uint32_t                       m_ssThresh;             //Slow Start Threshold
+     uint32_t                       m_initialCWnd;          //Initial cWnd value
+ 
+     uint32_t                       remoteRecvWnd; //Congestion window
+ 
+     //persist timer management
+     Time                           m_persistTime;
+     EventId                        m_persistEvent;
+ 
+     Ptr<MpTcpSocketBase> Copy ();
+ 
+     PendingData*   m_pendingData;
+     SequenceNumber32 m_firstPendingSequence;
+ 
+     //sequence info, next expected sequence number for sender & receiver side
+     uint64_t nextTxSequence;       // sequence number used by the multipath capable sender
+     uint32_t unAckedDataCount;     // Number of outstanding bytes
+     uint32_t congestionWnd;
+     uint64_t nextRxSequence;
+     DSNMapping* lastRetransmit;
+ 
+     SequenceNumber32 m_lastRxAck;
+ 
+     bool     m_skipRetxResched;
+     uint32_t m_dupAckCount;
+ 
+     EventId  m_lastAckEvent;
+ 
+     EventId  m_delAckEvent;
+     uint32_t m_delAckCount;
+     uint32_t m_delAckMaxCount;
+     Time     m_delAckTimeout;
+ 
+       // statistical variables
+       uint32_t nbRejected;
+       uint32_t nbReceived;
+ 
+       // methods for packet reordering
+       OptDSACK* createOptDSACK(OptDataSeqMapping * optDSN);
+ 
+       // we need this map because when an ACK is received all segments with lower sequence number are droped from the temporary buffer
+       map<uint64_t, uint32_t> retransSeg; // Retransmitted_Segment (data_Seq_Number, data_length)
+       map<uint64_t, uint8_t>  ackedSeg;   // Acked_Segment (data_Seq_Number, number_of_ack)
+       FRtoStep_t frtoStep;
+       bool useFastRecovery;
+ 
+ };
+ 
+ } // namespace ns3
+ 
+ #endif /* MP_TCP_SOCKET_BASE_H */
diff -crBN old/ns-3.13/src/mptcp/model/mp-tcp-typedefs.cc new/ns-3.13/src/mptcp/model/mp-tcp-typedefs.cc
*** old/ns-3.13/src/mptcp/model/mp-tcp-typedefs.cc	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/model/mp-tcp-typedefs.cc	2012-12-18 10:29:12.401669000 +0100
***************
*** 0 ****
--- 1,598 ----
+ #include <stdint.h>
+ #include <iostream>
+ #include "ns3/buffer.h"
+ #include "ns3/address-utils.h"
+ #include "ns3/log.h"
+ #include "mp-tcp-typedefs.h"
+ #include <stdlib.h>
+ #include <queue>
+ #include "ns3/traced-value.h"
+ #include "ns3/trace-source-accessor.h"
+ #include <ns3/object-base.h>
+ #include "ns3/simulator.h"
+ #include "ns3/tcp-typedefs.h"
+ #include "time.h"
+ 
+ NS_LOG_COMPONENT_DEFINE ("MpTcpTypeDefs");
+ namespace ns3 {
+ 
+ NS_OBJECT_ENSURE_REGISTERED (MpTcpSubFlow);
+ 
+ DSNMapping::DSNMapping ()
+ {
+     subflowIndex     = 255;
+     acknowledgement  = 0;
+     dataSeqNumber    = 0;
+     dataLevelLength  = 0;
+     subflowSeqNumber = 0;
+     dupAckCount      = 0;
+     packet           = 0;
+     //original         = true;
+     retransmited     = false;
+     tsval = Simulator::Now ().GetMilliSeconds (); // set the current time as a TimesTamp
+ }
+ 
+ DSNMapping::DSNMapping (uint8_t sFlowIdx, uint64_t dSeqNum, uint16_t dLvlLen, uint32_t sflowSeqNum, uint32_t ack, Ptr<Packet> pkt)
+ {
+     subflowIndex     = sFlowIdx;
+     dataSeqNumber    = dSeqNum;
+     dataLevelLength  = dLvlLen;
+     subflowSeqNumber = sflowSeqNum;
+     acknowledgement  = ack;
+     dupAckCount      = 0;
+     packet = new uint8_t[dLvlLen];
+     pkt->CopyData(packet, dLvlLen);
+ 
+     retransmited     = false;
+     tsval = Simulator::Now ().GetMilliSeconds (); // set the current time as a TimesTamp
+     //original         = true;
+ }
+ /*
+ DSNMapping::DSNMapping (const DSNMapping &res)
+ {
+     subflowIndex     = res.subflowIndex;
+     acknowledgement  = res.acknowledgement;
+     dataSeqNumber    = res.dataSeqNumber;
+     dataLevelLength  = res.dataLevelLength;
+     subflowSeqNumber = res.subflowSeqNumber;
+     dupAckCount      = res.dupAckCount;
+     packet           = res.packet;
+     original         = false;
+ }
+ */
+ DSNMapping::~DSNMapping()
+ {
+     /*
+     if ( original == false )
+         return;
+         */
+     dataSeqNumber    = 0;
+     dataLevelLength  = 0;
+     subflowSeqNumber = 0;
+     dupAckCount      = 0;
+     if( packet != 0 )
+         delete[] packet;
+ }
+ 
+ bool
+ DSNMapping::operator < (const DSNMapping& rhs) const
+ {
+ 	return this->dataSeqNumber < rhs.dataSeqNumber;
+ }
+ 
+ DataBuffer::DataBuffer ()
+ {
+     bufMaxSize    = 0;
+ }
+ 
+ DataBuffer::DataBuffer (uint32_t size)
+ {
+     bufMaxSize    = size;
+ }
+ 
+ DataBuffer::~DataBuffer ()
+ {
+     bufMaxSize    = 0;
+ }
+ 
+ uint32_t
+ DataBuffer::Add (uint8_t* buf, uint32_t size)
+ {
+     // read data from buf and insert it into the DataBuffer instance
+     NS_LOG_FUNCTION (this << (int) size << (int) (bufMaxSize - (uint32_t) buffer.size()) );
+     uint32_t toWrite = std::min(size, (bufMaxSize - (uint32_t) buffer.size()));
+ 
+     if(buffer.empty() == true)
+     {
+         NS_LOG_INFO("DataBuffer::Add -> buffer is empty !");
+     }else
+         NS_LOG_INFO("DataBuffer::Add -> buffer was not empty !");
+ 
+     uint32_t qty = 0;
+ 
+     while( qty < toWrite )
+     {
+         buffer.push( buf[ qty ] );
+         qty++;
+     }
+     NS_LOG_INFO("DataBuffer::Add -> amount of data = "<< qty);
+     NS_LOG_INFO("DataBuffer::Add -> freeSpace Size = "<< (bufMaxSize - (uint32_t) buffer.size()) );
+     return qty;
+ }
+ 
+ uint32_t
+ DataBuffer::Retrieve (uint8_t* buf, uint32_t size)
+ {
+     NS_LOG_FUNCTION (this << (int) size << (int)  (bufMaxSize - (uint32_t) buffer.size()) );
+     uint32_t quantity = std::min(size, (uint32_t) buffer.size());
+     if( quantity == 0)
+     {
+         NS_LOG_INFO("DataBuffer::Retrieve -> No data to read from buffer reception !");
+         return 0;
+     }
+ 
+     for(uint32_t i = 0; i < quantity; i++)
+     {
+         buf[i] = buffer.front();
+         buffer.pop();
+     }
+ 
+     NS_LOG_INFO("DataBuffer::Retrieve -> freeSpaceSize == "<< bufMaxSize - (uint32_t) buffer.size() );
+     return quantity;
+ }
+ 
+ Ptr<Packet>
+ DataBuffer::CreatePacket (uint32_t size)
+ {
+     NS_LOG_FUNCTION (this << (int) size << (int) ( bufMaxSize - (uint32_t) buffer.size()) );
+     uint32_t quantity = std::min(size, (uint32_t) buffer.size());
+     if( quantity == 0 )
+     {
+         NS_LOG_INFO("DataBuffer::CreatePacket -> No data ready for sending !");
+         return 0;
+     }
+ 
+     uint8_t *ptrBuffer = new uint8_t [quantity];
+     for( uint32_t i = 0; i < quantity; i++)
+     {
+         ptrBuffer [i] = buffer.front();
+         buffer.pop();
+     }
+ 
+     Ptr<Packet> pkt = new Packet (ptrBuffer, quantity);
+     delete[] ptrBuffer;
+ 
+     NS_LOG_INFO("DataBuffer::CreatePacket -> freeSpaceSize == "<< bufMaxSize - (uint32_t) buffer.size() );
+     return pkt;
+ }
+ 
+ uint32_t
+ DataBuffer::ReadPacket (Ptr<Packet> pkt, uint32_t dataLen)
+ {
+     NS_LOG_FUNCTION (this << (int) (bufMaxSize - (uint32_t) buffer.size()) );
+ 
+     uint32_t toWrite = std::min(dataLen, ( bufMaxSize - (uint32_t) buffer.size()) );
+ 
+     if(buffer.empty() == true)
+     {
+         NS_LOG_INFO("DataBuffer::ReadPacket -> buffer is empty !");
+     }else
+         NS_LOG_INFO("DataBuffer::ReadPacket -> buffer was not empty !");
+ 
+     uint8_t *ptrBuffer = new uint8_t [toWrite];
+     pkt->CopyData (ptrBuffer, toWrite);
+ 
+     for(uint32_t i =0; i < toWrite; i++)
+         buffer.push( ptrBuffer[i] );
+     delete[] ptrBuffer;
+ 
+     NS_LOG_INFO("DataBuffer::ReadPacket -> data   readed == "<< toWrite );
+     NS_LOG_INFO("DataBuffer::ReadPacket -> freeSpaceSize == "<< bufMaxSize - (uint32_t) buffer.size() );
+     return toWrite;
+ }
+ 
+ uint32_t
+ DataBuffer::PendingData ()
+ {
+     return ( (uint32_t) buffer.size() );
+ }
+ 
+ uint32_t
+ DataBuffer::FreeSpaceSize ()
+ {
+     return (bufMaxSize - (uint32_t) buffer.size());
+ }
+ 
+ bool
+ DataBuffer::Empty ()
+ {
+     return buffer.empty(); // ( freeSpaceSize == bufMaxSize );
+ }
+ 
+ bool
+ DataBuffer::Full ()
+ {
+     return (bufMaxSize == (uint32_t) buffer.size());//( freeSpaceSize == 0 );
+ }
+ 
+ MpTcpStateMachine::MpTcpStateMachine ()
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     aT[CLOSED][APP_LISTEN]   = SA (LISTEN,   NO_ACT);
+     aT[CLOSED][APP_CONNECT]  = SA (SYN_SENT, SYN_TX);
+     aT[CLOSED][APP_SEND]     = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][SEQ_RECV]     = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][APP_CLOSE]    = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][TIMEOUT]      = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][ACK_RX]       = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][SYN_RX]       = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][SYN_ACK_RX]   = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][FIN_RX]       = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][FIN_ACK_RX]   = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][RST_RX]       = SA (CLOSED,   NO_ACT);
+     aT[CLOSED][BAD_FLAGS]    = SA (CLOSED,   NO_ACT);
+ 
+ 
+     aT[LISTEN][APP_CLOSE]    = SA (CLOSING,  FIN_TX);
+     aT[LISTEN][SEQ_RECV]     = SA (LISTEN,   NEW_SEQ_RX);
+     aT[LISTEN][ACK_RX]       = SA (LISTEN,   NEW_SEQ_RX);  // assert in case where no syn has been received
+     aT[LISTEN][SYN_RX]       = SA (SYN_RCVD, SYN_ACK_TX);  // stay in listen and do fork
+     aT[LISTEN][FIN_RX]       = SA (CLOSED,   FIN_ACK_TX);
+     aT[LISTEN][FIN_ACK_RX]   = SA (CLOSED,   NO_ACT);
+ 
+     aT[SYN_RCVD][APP_SEND]   = SA (SYN_RCVD, NO_ACT);
+     aT[SYN_RCVD][SEQ_RECV]   = SA (SYN_RCVD, NO_ACT);
+     aT[SYN_RCVD][APP_CLOSE]  = SA (SYN_RCVD, NO_ACT);
+     aT[SYN_RCVD][TIMEOUT]    = SA (SYN_RCVD, NO_ACT);
+     aT[SYN_RCVD][ACK_RX]     = SA (LISTEN,   SERV_NOTIFY);
+     aT[SYN_RCVD][SYN_RX]     = SA (SYN_RCVD, NO_ACT);
+     aT[SYN_RCVD][SYN_ACK_RX] = SA (SYN_RCVD, NO_ACT);
+     aT[SYN_RCVD][FIN_RX]     = SA (SYN_RCVD, NO_ACT);
+     aT[SYN_RCVD][FIN_ACK_RX] = SA (SYN_RCVD, NO_ACT);
+     aT[SYN_RCVD][RST_RX]     = SA (SYN_RCVD, NO_ACT);
+     aT[SYN_RCVD][BAD_FLAGS]  = SA (SYN_RCVD, NO_ACT);
+ 
+     aT[SYN_SENT][APP_SEND]   = SA (SYN_SENT, NO_ACT);
+     aT[SYN_SENT][APP_CLOSE]  = SA (CLOSED,   NO_ACT);
+     aT[SYN_SENT][SYN_ACK_RX] = SA (ESTABLISHED, ACK_TX_1); // send ack to confirm connection establishment
+     aT[SYN_SENT][FIN_RX]     = SA (CLOSED,   FIN_ACK_TX);
+     aT[SYN_SENT][FIN_ACK_RX] = SA (CLOSED,   NO_ACT);
+ 
+     aT[ESTABLISHED][APP_LISTEN]  = SA (ESTABLISHED, NO_ACT);
+     aT[ESTABLISHED][APP_CONNECT] = SA (ESTABLISHED, NO_ACT);
+     aT[ESTABLISHED][APP_SEND]    = SA (ESTABLISHED, TX_DATA);
+     aT[ESTABLISHED][SEQ_RECV]    = SA (ESTABLISHED, NEW_SEQ_RX);
+     aT[ESTABLISHED][APP_CLOSE]   = SA (CLOSING,     FIN_TX);
+     aT[ESTABLISHED][TIMEOUT]     = SA (ESTABLISHED, RETX);
+     aT[ESTABLISHED][ACK_RX]      = SA (ESTABLISHED, NEW_ACK);
+     aT[ESTABLISHED][FIN_RX]      = SA (CLOSED,      FIN_ACK_TX);
+ 
+     aT[CLOSING][FIN_ACK_RX]  = SA (CLOSED,      NO_ACT);
+ 
+   // Create the flags lookup table
+   eV[ 0x00] = SEQ_RECV;  // No flags
+   eV[ 0x01] = FIN_RX;    // Fin
+   eV[ 0x02] = SYN_RX;    // Syn
+   eV[ 0x03] = BAD_FLAGS; // Illegal
+   eV[ 0x04] = RST_RX;    // Rst
+   eV[ 0x05] = BAD_FLAGS; // Illegal
+   eV[ 0x06] = BAD_FLAGS; // Illegal
+   eV[ 0x07] = BAD_FLAGS; // Illegal
+   eV[ 0x08] = SEQ_RECV;  // Psh flag is not used
+   eV[ 0x09] = FIN_RX;    // Fin
+   eV[ 0x0a] = SYN_RX;    // Syn
+   eV[ 0x0b] = BAD_FLAGS; // Illegal
+   eV[ 0x0c] = RST_RX;    // Rst
+   eV[ 0x0d] = BAD_FLAGS; // Illegal
+   eV[ 0x0e] = BAD_FLAGS; // Illegal
+   eV[ 0x0f] = BAD_FLAGS; // Illegal
+   eV[ 0x10] = ACK_RX;    // Ack
+   eV[ 0x11] = FIN_ACK_RX;// Fin/Ack
+   eV[ 0x12] = SYN_ACK_RX;// Syn/Ack
+   eV[ 0x13] = BAD_FLAGS; // Illegal
+   eV[ 0x14] = RST_RX;    // Rst
+   eV[ 0x15] = BAD_FLAGS; // Illegal
+   eV[ 0x16] = BAD_FLAGS; // Illegal
+   eV[ 0x17] = BAD_FLAGS; // Illegal
+   eV[ 0x18] = ACK_RX;    // Ack
+   eV[ 0x19] = FIN_ACK_RX;// Fin/Ack
+   eV[ 0x1a] = SYN_ACK_RX;// Syn/Ack
+   eV[ 0x1b] = BAD_FLAGS; // Illegal
+   eV[ 0x1c] = RST_RX;    // Rst
+   eV[ 0x1d] = BAD_FLAGS; // Illegal
+   eV[ 0x1e] = BAD_FLAGS; // Illegal
+   eV[ 0x1f] = BAD_FLAGS; // Illegal
+   eV[ 0x20] = SEQ_RECV;  // No flags (Urgent not presently used)
+   eV[ 0x21] = FIN_RX;    // Fin
+   eV[ 0x22] = SYN_RX;    // Syn
+   eV[ 0x23] = BAD_FLAGS; // Illegal
+   eV[ 0x24] = RST_RX;    // Rst
+   eV[ 0x25] = BAD_FLAGS; // Illegal
+   eV[ 0x26] = BAD_FLAGS; // Illegal
+   eV[ 0x27] = BAD_FLAGS; // Illegal
+   eV[ 0x28] = SEQ_RECV;  // Psh flag is not used
+   eV[ 0x29] = FIN_RX;    // Fin
+   eV[ 0x2a] = SYN_RX;    // Syn
+   eV[ 0x2b] = BAD_FLAGS; // Illegal
+   eV[ 0x2c] = RST_RX;    // Rst
+   eV[ 0x2d] = BAD_FLAGS; // Illegal
+   eV[ 0x2e] = BAD_FLAGS; // Illegal
+   eV[ 0x2f] = BAD_FLAGS; // Illegal
+   eV[ 0x30] = ACK_RX;    // Ack (Urgent not used)
+   eV[ 0x31] = FIN_ACK_RX;// Fin/Ack
+   eV[ 0x32] = SYN_ACK_RX;// Syn/Ack
+   eV[ 0x33] = BAD_FLAGS; // Illegal
+   eV[ 0x34] = RST_RX;    // Rst
+   eV[ 0x35] = BAD_FLAGS; // Illegal
+   eV[ 0x36] = BAD_FLAGS; // Illegal
+   eV[ 0x37] = BAD_FLAGS; // Illegal
+   eV[ 0x38] = ACK_RX;    // Ack
+   eV[ 0x39] = FIN_ACK_RX;// Fin/Ack
+   eV[ 0x3a] = SYN_ACK_RX;// Syn/Ack
+   eV[ 0x3b] = BAD_FLAGS; // Illegal
+   eV[ 0x3c] = RST_RX;    // Rst
+   eV[ 0x3d] = BAD_FLAGS; // Illegal
+   eV[ 0x3e] = BAD_FLAGS; // Illegal
+   eV[ 0x3f] = BAD_FLAGS; // Illegal
+ }
+ 
+ MpTcpStateMachine::~MpTcpStateMachine ()
+ {
+ }
+ 
+ string
+ MpTcpStateMachine::printEvent(Events_t e)
+ {
+     switch ( e )
+     {
+         case APP_LISTEN: return "APP_LISTEN";   // 0
+         case APP_CONNECT: return "APP_CONNECT";  // 1
+         case APP_SEND: return "APP_SEND";     // 2
+         case SEQ_RECV: return "SEQ_RECV";     // 3
+         case APP_CLOSE: return "APP_CLOSE";    // 4
+         case TIMEOUT: return "TIMEOUT";      // 5
+         case ACK_RX: return "ACK_RX";       // 6
+         case SYN_RX: return "SYN_RX";       // 7
+         case SYN_ACK_RX: return "SYN_ACK_RX";   // 8
+         case FIN_RX: return "FIN_RX";       // 9
+         case FIN_ACK_RX: return "FIN_ACK_RX";   // 10
+         case RST_RX: return "RST_RX";       // 11
+         case BAD_FLAGS: return "BAD_FLAGS";    // 12
+         case LAST_EVENT: return "LAST_EVENT";
+         default: return "Unrecognized event";
+     }
+ }
+ 
+ string
+ MpTcpStateMachine::printAction(Actions_t a)
+ {
+     switch ( a )
+     {
+         case NO_ACT: return "NO_ACT";       // 0
+         case ACK_TX: return "ACK_TX";       // 1
+         case ACK_TX_1: return "ACK_TX_1";     // 2 - ACK response to syn
+         case RST_TX: return "RST_TX";       // 3
+         case SYN_TX: return "SYN_TX";       // 4
+         case SYN_ACK_TX: return "SYN_ACK_TX";   // 5
+         case FIN_TX: return "FIN_TX";       // 6
+         case FIN_ACK_TX: return "FIN_ACK_TX";   // 7
+         case NEW_ACK: return "NEW_ACK";      // 8
+         case NEW_SEQ_RX: return "NEW_SEQ_RX";   // 9
+         case RETX: return "RETX";         // 10
+         case TX_DATA: return "TX_DATA";      // 11
+         case PEER_CLOSE: return "PEER_CLOSE";   // 12
+         case APP_CLOSED: return "APP_CLOSED";   // 13
+         case CANCEL_TM: return "CANCEL_TM";    // 14
+         case APP_NOTIFY: return "APP_NOTIFY";   // 15 - Notify app that connection failed
+         case SERV_NOTIFY: return "SERV_NOTIFY";  // 16 - Notify server tcp that connection completed
+         case LAST_ACTION: return "LAST_ACTION";
+         default: return "Unrecognized action";
+     }
+ }
+ 
+ string
+ MpTcpStateMachine::printState(TcpStates_t s)
+ {
+     switch ( s )
+     {
+         case CLOSED: return "CLOSED";       // 0
+         case LISTEN: return "LISTEN";       // 1
+         case SYN_SENT: return "SYN_SENT";     // 2
+         case SYN_RCVD: return "SYN_RCVD";     // 3
+         case ESTABLISHED: return "ESTABLISHED";  // 4
+         case CLOSE_WAIT: return "CLOSE_WAIT";   // 5
+         case LAST_ACK: return "LAST_ACK";     // 6
+         case FIN_WAIT_1: return "FIN_WAIT_1";   // 7
+         case FIN_WAIT_2: return "FIN_WAIT_2";   // 8
+         case CLOSING: return "CLOSING";      // 9
+         case TIME_WAIT: return "TIME_WAIT";   // 10
+         case LAST_STATE: return "LAST_STATE";
+         default: return "state unrecognized";
+     }
+ }
+ 
+ TypeId
+ MpTcpSubFlow::GetTypeId (void)
+ {
+     static TypeId tid = TypeId ("ns3::MpTcpSubFlow")
+         .SetParent (Object::GetTypeId ())
+         //.AddConstructor<MpTcpSubFlow> ()
+         .AddTraceSource ("CongestionWindow",
+                          "The congestion control window to trace.",
+                          MakeTraceSourceAccessor (&MpTcpSubFlow::cwnd))
+         ;
+       return tid;
+ }
+ 
+ MpTcpSubFlow::MpTcpSubFlow()
+     : routeId (0), state (CLOSED), phase (Slow_Start),
+       sAddr (Ipv4Address::GetZero ()), sPort (0),
+       dAddr (Ipv4Address::GetZero ()), dPort (0),
+       oif (0), mapDSN (0), lastMeasuredRtt (Seconds (0.0))
+ {
+     connected   = false;
+     TxSeqNumber = rand() % 1000;
+     RxSeqNumber = 0;
+     bandwidth   = 0;
+     cwnd        = 1;                  // congestion window is initialized to one segment
+     scwnd       = 0;
+     ssthresh    = 65535;              // initial value for a TCP connexion
+     maxSeqNb    = TxSeqNumber - 1;    // thus we suppose that SYN & ACK segments has been acked correctly, for subflow n° 0
+     highestAck  = 0;
+     rtt = new RttMeanDeviation ();
+     rtt->Gain(0.1); // 1.0
+ 
+     // variables used for simulating drops
+     LostThreshold     = 0.0;
+     CanDrop           = true;
+     PktCount          = 0;
+     MaxPktCount       = rand() % 100 + 50;
+     DropedPktCount    = 0;
+     MaxDropedPktCount = 1;
+ 
+     // variables used for reordering simulation
+     savedCWND         = 0.0;
+     savedSSThresh     = 0;
+     SpuriousRecovery  = false;
+     recover           = 0;
+     ackCount          = 0;
+     ReTxSeqNumber     = 0;
+     nbRecvAck         = -1;
+ }
+ 
+ MpTcpSubFlow::MpTcpSubFlow(uint32_t TxSeqNb)
+     : routeId (0), state (CLOSED), phase (Slow_Start),
+       sAddr (Ipv4Address::GetZero ()), sPort (0),
+       dAddr (Ipv4Address::GetZero ()), dPort (0),
+       oif (0), mapDSN (0), lastMeasuredRtt (Seconds (0.0))
+ {
+     connected   = false;
+     TxSeqNumber = TxSeqNb;
+     RxSeqNumber = 0;
+     bandwidth   = 0;
+     cwnd        = 1;                   // congestion window is initialized to one segment
+     scwnd       = 0;
+     ssthresh    = 65535;               // initial value for a TCP connexion
+     maxSeqNb    = TxSeqNumber - 1;     // the subflow is created after receiving 'SYN ACK' segment
+     highestAck  = 0;
+     rtt = new RttMeanDeviation ();
+     rtt->Gain(0.1); //1.0
+ 
+     // variables used for simulating drops
+     LostThreshold     = 0.0;
+     CanDrop           = true;
+     PktCount          = 0;
+     MaxPktCount       = rand() % 100 + 100;
+     DropedPktCount    = 0;
+     MaxDropedPktCount = 1;
+ 
+     // variables used for reordering simulation
+     savedCWND         = 0.0;
+     savedSSThresh     = 0;
+     SpuriousRecovery  = false;
+     recover           = 0;
+     ackCount          = 0;
+     ReTxSeqNumber     = 0;
+ }
+ 
+ MpTcpSubFlow::~MpTcpSubFlow()
+ {
+     routeId     = 0;
+     sAddr       = Ipv4Address::GetZero ();
+     oif         = 0;
+     state       = CLOSED;
+     bandwidth   = 0;
+     cwnd        = 1;
+     maxSeqNb    = 0;
+     highestAck  = 0;
+     for(list<DSNMapping *>::iterator it = mapDSN.begin(); it != mapDSN.end(); ++it)
+     {
+         DSNMapping * ptrDSN = *it;
+         delete ptrDSN;
+     }
+     mapDSN.clear();
+ }
+ 
+ void
+ MpTcpSubFlow::StartTracing (string traced)
+ {
+     NS_LOG_INFO ("MpTcpSubFlow -> starting tracing of: "<< traced);
+     TraceConnectWithoutContext (traced, MakeCallback (&MpTcpSubFlow::CwndTracer, this)); //"CongestionWindow"
+ }
+ 
+ void
+ MpTcpSubFlow::CwndTracer (double oldval, double newval)
+ {
+     NS_LOG_WARN ("Subflow "<< routeId <<": Moving cwnd from " << oldval << " to " << newval);
+ }
+ 
+ void
+ MpTcpSubFlow::AddDSNMapping(uint8_t sFlowIdx, uint64_t dSeqNum, uint16_t dLvlLen, uint32_t sflowSeqNum, uint32_t ack, Ptr<Packet> pkt)
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     mapDSN.push_back ( new DSNMapping(sFlowIdx, dSeqNum, dLvlLen, sflowSeqNum, ack, pkt) );
+ }
+ 
+ void
+ MpTcpSubFlow::updateRTT (uint32_t ack, Time current)
+ {
+     NS_LOG_FUNCTION( this << ack << current );
+ //    rtt->AckSeq (SequenceNumber32(unsigned(ack),signed(ack)));
+ //    rtt->AckSeq (SequenceNumber32 (make_pair <u_int32_t, int> (ack, (int) ack)));
+       rtt->AckSeq (SequenceNumber32 (ack));
+     NS_LOG_INFO ("MpTcpSubFlow::updateRTT -> time from last RTT measure = " << (current - lastMeasuredRtt).GetSeconds() );
+ /*
+     rtt->Measurement ( current - lastMeasuredRtt );
+     lastMeasuredRtt = current;
+     measuredRTT.insert(measuredRTT.end(), rtt->Estimate().GetSeconds ());
+ */
+     Time temp= rtt->GetCurrentEstimate();
+     measuredRTT.insert(measuredRTT.end(), temp.GetSeconds());
+ 
+     NS_LOG_INFO ("MpTcpSubFlow::updateRTT -> estimated RTT = " << (temp.GetSeconds ()) );
+ }
+ 
+ DSNMapping *
+ MpTcpSubFlow::GetunAckPkt (uint32_t awnd)
+ {
+     NS_LOG_FUNCTION_NOARGS();
+     DSNMapping * ptrDSN = 0;
+ 
+     for (list<DSNMapping *>::iterator it = mapDSN.begin(); it != mapDSN.end(); ++it)
+     {
+         DSNMapping * ptr = *it;
+         NS_LOG_ERROR ("Subflow ("<<(int) routeId<<") Subflow Seq N° = " << ptr->subflowSeqNumber);
+         if ( (ptr->subflowSeqNumber == highestAck + 1) || (ptr->subflowSeqNumber == highestAck + 2) )
+         {
+             // we added 2, for the case in wich the fst pkt of a subsequent subflow is lost, because the highest ack is the one included in 'SYN | ACK' which is 2 less than the current TxSeq
+             NS_LOG_INFO ("MpTcpSubFlow::GetunAckPkt -> packet to retransmit found: sFlowSeqNum = " << ptr->subflowSeqNumber);
+             /*
+             if ( awnd < ptr->dataLevelLength )
+             {
+                 DSNMapping * fstPtr = new DSNMapping(ptr->subflowIndex, ptr->dataSeqNumber, (uint16_t)awnd, ptr->subflowSeqNumber, ptr->acknowledgement, new Packet(ptr->packet, awnd));
+                 DSNMapping * sndPtr = new DSNMapping(ptr->subflowIndex, ptr->dataSeqNumber + (uint64_t)awnd, ptr->dataLevelLength - (uint16_t) awnd, ptr->subflowSeqNumber + awnd, ptr->acknowledgement, new Packet(ptr->packet + awnd,(uint32_t)ptr->dataLevelLength - awnd));
+                 delete ptr;
+                 ptr = fstPtr;
+                 mapDSN.insert( mapDSN.end(), sndPtr);
+             }
+             */
+             ptrDSN = ptr;
+             //mapDSN.erase (it);
+             break;
+         }
+     }
+     return ptrDSN;
+ }
+ 
+ MpTcpAddressInfo::MpTcpAddressInfo()
+     : addrID (0), ipv4Addr (Ipv4Address::GetZero ()), mask (Ipv4Mask::GetZero())
+ {
+ }
+ 
+ MpTcpAddressInfo::~MpTcpAddressInfo()
+ {
+     addrID = 0;
+     ipv4Addr = Ipv4Address::GetZero ();
+ }
+ 
+ } // namespace ns3
diff -crBN old/ns-3.13/src/mptcp/model/mp-tcp-typedefs.h new/ns-3.13/src/mptcp/model/mp-tcp-typedefs.h
*** old/ns-3.13/src/mptcp/model/mp-tcp-typedefs.h	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/model/mp-tcp-typedefs.h	2012-11-07 09:26:37.017498000 +0100
***************
*** 0 ****
--- 1,209 ----
+ #include <vector>
+ #include <map>
+ #include "ns3/sequence-number.h"
+ #include "ns3/rtt-estimator.h"
+ #include "ns3/tcp-typedefs.h"
+ #include "ns3/ipv4-address.h"
+ #include "ns3/event-id.h"
+ #include <stdint.h>
+ #include <queue>
+ #include <list>
+ #include <set>
+ 
+ #include "ns3/object.h"
+ #include "ns3/uinteger.h"
+ #include "ns3/traced-value.h"
+ #include "ns3/trace-source-accessor.h"
+ 
+ #ifndef MP_TCP_TYPEDEFS_H
+ #define MP_TCP_TYPEDEFS_H
+ 
+ using namespace std;
+ 
+ namespace ns3 {
+ 
+ typedef enum {
+   MP_NONE,        // 0
+   MP_MPC,         // 1
+   MP_ADDR,        // 2
+   MP_JOIN} MpStates_t;
+ // Multipath actions
+ 
+ // congestion control algorithm
+ typedef enum {
+   Uncoupled_TCPs,       // 0
+   Linked_Increases,     // 1
+   RTT_Compensator,      // 2
+   Fully_Coupled         // 3
+   } CongestionCtrl_t;
+ 
+ // connection phase
+ typedef enum {
+   Slow_Start,                   // 0
+   Congestion_Avoidance,         // 1
+   DSACK_SS,                     // 2 DSACK Slow Start: a temporary slow start triggered after detecting spurious retransmission based on DSACK information
+   RTO_Recovery                  // 3 Reconvery algorithm after RTO expiration
+   } Phase_t;
+ 
+ typedef enum {
+   Round_Robin        // 0
+   //Collision_Avoidance         // 1
+   } DataDistribAlgo_t;
+ 
+ typedef enum {
+   NoPR_Algo,    // 0
+   Eifel,        // 1
+   TCP_DOOR,     // 2 Detection of Out-of-Order and Response
+   D_SACK,       // 3 Duplicate SACK (Selective ACKnowledgement)
+   F_RTO         // 4 Forward RTO-Recovery: Algorithm for detecting spurious retransmission timeouts
+   } PacketReorder_t;
+ 
+ typedef enum {
+   Step_1,       // 0
+   Step_2,       // 1
+   Step_3,       // 2
+   Step_4        // 3 In this step of F-RTO do a standard Fast Recovery algorithm
+   } FRtoStep_t;
+ 
+ class DSNMapping
+ {
+ public:
+     DSNMapping ();
+     DSNMapping (uint8_t sFlowIdx, uint64_t dSeqNum, uint16_t dLvlLen, uint32_t sflowSeqNum, uint32_t ack, Ptr<Packet> pkt);
+     //DSNMapping (const DSNMapping &res);
+     virtual ~DSNMapping();
+     uint64_t dataSeqNumber;
+     uint16_t dataLevelLength;
+     uint32_t subflowSeqNumber;
+     uint32_t acknowledgement;
+     uint32_t dupAckCount;
+     uint8_t  subflowIndex;
+     uint8_t *packet;
+ 
+     bool operator <  (const DSNMapping& rhs) const;
+ 
+     // variables for reordering simulation
+     // Eifel Algorithm
+     bool     retransmited;
+     uint64_t tsval; // TimesTamp value
+ 
+ /*
+ private:/
+     bool original;
+     */
+ };
+ 
+ typedef enum {
+   NO_ACTION,       // 0
+   ADDR_TX,
+   INIT_SUBFLOWS} MpActions_t;
+ 
+ class MpTcpStateMachine : public TcpStateMachine
+ {
+ public:
+ 
+     MpTcpStateMachine();
+     virtual ~MpTcpStateMachine();
+ 
+     string printState(TcpStates_t s);
+     string printEvent(Events_t e);
+     string printAction(Actions_t a);
+ 
+ };
+ 
+ class MpTcpSubFlow : public Object
+ {
+ public:
+     static TypeId GetTypeId (void);
+ 
+     MpTcpSubFlow ();
+     ~MpTcpSubFlow ();
+     MpTcpSubFlow (uint32_t TxSeqNb);
+ 
+     void StartTracing (string traced);
+     void CwndTracer (double oldval, double newval);
+ 
+     void AddDSNMapping(uint8_t sFlowIdx, uint64_t dSeqNum, uint16_t dLvlLen, uint32_t sflowSeqNum, uint32_t ack, Ptr<Packet> pkt);
+     void updateRTT (uint32_t ack, Time current);
+     DSNMapping * GetunAckPkt (uint32_t awnd);
+ 
+     uint16_t    routeId;
+     bool        connected;
+     TcpStates_t    state;
+     Phase_t     phase;
+     Ipv4Address sAddr;
+     uint16_t    sPort;
+     Ipv4Address dAddr;
+     uint16_t    dPort;
+     uint32_t    oif;
+ 
+     EventId  retxEvent;
+     uint32_t MSS;          // Maximum Segment Size
+     //double   cwnd;
+     TracedValue<double> cwnd;
+     double   scwnd;         // smoothed congestion window
+     uint32_t ssthresh;
+     uint32_t maxSeqNb;     // it represent the highest sequence number of a sent byte. In general it's egual to ( TxSeqNumber - 1 ) until a retransmission happen
+     uint32_t highestAck;   // hightest received ACK for the subflow level sequence number
+     uint64_t bandwidth;
+ 
+     list<DSNMapping *> mapDSN;
+     multiset<double> measuredRTT;
+     //list<double> measuredRTT;
+     Ptr<RttMeanDeviation> rtt;
+     Time     lastMeasuredRtt;
+     uint32_t TxSeqNumber;
+     uint32_t RxSeqNumber;
+ 
+     // for losses simulation
+     double   LostThreshold;
+     bool     CanDrop;
+     uint64_t PktCount;
+     uint64_t MaxPktCount;
+     uint32_t DropedPktCount;
+     uint32_t MaxDropedPktCount;
+ 
+     // Reordering simulation
+     double   savedCWND;
+     uint32_t savedSSThresh;
+     bool     SpuriousRecovery;
+     uint32_t recover;
+     uint8_t  ackCount;      // count of received acknowledgement after an RTO expiration
+     uint32_t ReTxSeqNumber; // higher sequence number of the retransmitted segment
+     int      nbRecvAck;
+ };
+ 
+ class MpTcpAddressInfo
+ {
+ public:
+     MpTcpAddressInfo();
+     ~MpTcpAddressInfo();
+ 
+     uint8_t     addrID;
+     Ipv4Address ipv4Addr;
+     Ipv4Mask    mask;
+ };
+ 
+ class DataBuffer
+ {
+ public:
+     DataBuffer();
+     DataBuffer(uint32_t size);
+     ~DataBuffer();
+ 
+     queue<uint8_t> buffer;
+     uint32_t bufMaxSize;
+ 
+     uint32_t Add(uint8_t* buf, uint32_t size);
+     uint32_t Retrieve(uint8_t* buf, uint32_t size);
+     Ptr<Packet> CreatePacket (uint32_t size);
+     uint32_t ReadPacket (Ptr<Packet> pkt, uint32_t dataLen);
+     bool     Empty();
+     bool     Full ();
+     uint32_t PendingData();
+     uint32_t FreeSpaceSize();
+ };
+ 
+ 
+ }//namespace ns3
+ #endif //MP_TCP_TYPEDEFS_H
diff -crBN old/ns-3.13/src/mptcp/waf new/ns-3.13/src/mptcp/waf
*** old/ns-3.13/src/mptcp/waf	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/waf	2012-11-07 09:26:37.017498000 +0100
***************
*** 0 ****
--- 1 ----
+ exec "`dirname "$0"`"/../../waf "$@"
\ No newline at end of file
diff -crBN old/ns-3.13/src/mptcp/wscript new/ns-3.13/src/mptcp/wscript
*** old/ns-3.13/src/mptcp/wscript	1970-01-01 01:00:00.000000000 +0100
--- new/ns-3.13/src/mptcp/wscript	2012-11-07 09:26:37.017498000 +0100
***************
*** 0 ****
--- 1,36 ----
+ ## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-
+ 
+ def build(bld):
+     obj = bld.create_ns3_module('mptcp', ['core','wifi','network','propagation','bridge','internet','mpi','applications'])
+     obj.source = [
+         'model/mp-tcp-socket-base.cc',
+         'model/mp-tcp-header.cc',
+         'model/mp-tcp-l4-protocol.cc',
+         'model/mp-tcp-typedefs.cc',
+         'helper/mp-internet-stack-helper.cc',          
+         ]
+ 
+     obj_test = bld.create_ns3_module_test_library('mptcp')
+     obj_test.source = [
+         ]
+ 
+     headers = bld.new_task_gen(features=['ns3header'])  
+     headers.module = 'mptcp'
+     headers.source = [
+         'model/mp-tcp-socket-base.h',
+         'model/mp-tcp-header.h',
+         'model/mp-tcp-l4-protocol.h',
+         'model/mp-tcp-typedefs.h',
+         'helper/mp-internet-stack-helper.h',             
+         ]
+ 
+     
+ 
+ #if bld.env['ENABLE_GSL']:
+ #      obj.use.extend(['GSL', 'GSLCBLAS', 'M'])
+ #      obj_test.use.extend(['GSL', 'GSLCBLAS', 'M'])
+ 
+ #if (bld.env['ENABLE_EXAMPLES']):
+ #     bld.add_subdirs('examples')
+ 
+ #bld.ns3_python_bindings()
