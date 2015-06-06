ENGG4802 thesis
==================

Organisation: [CEIT](http://ceit.uq.edu.au) at [The University of Queensland](http://www.uq.edu.au).
Supervisor: [Mark Schulz](https://github.com/mschulz)

Title: Technology-supported activities through realtime, distributed, and collaborative interfaces

Abstract: Traditionally user interfaces have been designed for a single user using a single, expected device—e.g. someone on a computer visiting a website. With the advent and lowering costs of the internet and mobile devices, interfaces are now often distributed and collaborative. While there have been attempts to to handle this (e.g. Google Docs), they have so far been in a limited, prescribed manner. In this proposal, a project is put forward to design and build a new approach for a distributed and collaborative user interface focusing on the concept of having a workspace with avail- able objects and data sources that the user is able to freely use. The experimental applications will be with a remote laboratory experiment and learning programming.

Prototype: Arduino using DDP with a colour sensor
--------

In order to demonstrate the thesis a [demonstration workspace](https://github.com/jesse-c/thesis-workspace) was created with the purpose being for students to collaborate together and learn about pulse width modulation and simple colour theory. To do this an Arduino had a [colour sensor](https://www.sparkfun.com/products/retired/10904) and an RGB LED. It communicated with the server and other clients via DDP requiring me to build an [Arduino DDP library](https://github.com/jesse-c/Arduino-DDP).
