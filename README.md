ENGG4802 thesis
==================

([thesis](https://github.com/jesse-c/thesis))

Organisation: [CEIT](http://ceit.uq.edu.au) at [The University of Queensland](http://www.uq.edu.au)

Supervisor: [Mark Schulz](https://github.com/mschulz)

Title: Technology-supported activities through realtime, distributed, and collaborative interfaces

Abstract: Traditionally user interfaces have been designed for a single user using one common device type---e.g. someone on a computer visiting a website. With the internet and mobile devices now being commonplace, interfaces could take advantage of being distributed across devices and working collaboratively with others in real-time. While there have been attempts to to handle this (e.g. Google Docs), they have so far been in a limited, prescribed manner. A proposed concept is put forward to design and build a new approach for a distributed and real-time collaborative user interface focusing on the concept of having a workspace with components that the user is able to freely use in a real-time manner. It is based upon existing web browsers and devices. Parts of the UI can be distributed across separate platforms. A prototype of a workspace for education is included and user testing of the prototype shows positive experiences and results for the users.

Prototype: Arduino using DDP with a colour sensor
--------

In order to demonstrate the thesis a [demonstration workspace](https://github.com/jesse-c/thesis-workspace) was created with the purpose being for students to collaborate together and learn about pulse width modulation and simple colour theory. To do this an Arduino had a [colour sensor](https://www.sparkfun.com/products/retired/10904) and an RGB LED. It communicated with the server and other clients via DDP requiring me to build an [Arduino DDP library](https://github.com/jesse-c/Arduino-DDP).
