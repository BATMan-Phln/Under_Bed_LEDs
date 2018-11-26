# Under_Bed_LEDs
RGB LED strips under our bed controlled by Arduino

This is the first project that I've posted here.  

My project: Under bed lights

My skill Level:
      If I was a bit better, I could be considered a novice.  I’m trying very hard to learn coding but, due to the amount of medications that I take, I have a Swiss cheese brain.  I’ve been trying to learn this for a very long time.  This project is light years over my head but it’s something that we need done.  I appreciate any help I can get.

Hardware:
    o	2 sets of RGB LED strips (One on my side only and one on the foot and wife’s side)

    o	44 key remote with 6 programmable buttons (DIY)

    o	3 PIR motion sensors (1 on my side, one at my wife’s side and one at the foot aimed toward the door.

    o	2 “panic” buttons (1 on each bedside table)

    o	1 LDR

    o	1 Arduino Leonardo (it has more interrupt pins)

    o	12V battery and relay for power outages


Reason:
    I get up about every hour during the night.  I’d rather not wake my wife by turning on the ceiling or table light but it would still be nice to see.
	
Concept:
      A.	When I get up, the motion sensor under my side turns on only the LED strip on my side of the bed.  (Some low degree of purple set by the DIY button’s code sent via IR emitter)
      B.	When someone enters the room, the motion sensor under the foot of the bed turn all strips on.  (Some degree of white set by the DIY button’s code sent via IR emitter)
      C.	When my wife gets up, the motion sensor under her side turns all strips on.  (Some degree of pink set by the DIY button’s code sent via IR emitter)
      D.	When either of us hits either button on our bedside table, it will turn all strips on.  (Full white set by the DIY button’s code sent via IR emitter)
      E.	Retain the ability to use the remote control.  (Use the Arduino as a repeater)
      F.	LDR prevents lights from turning on during daylight hours.  (This will have to be set to a certain level due to blackout curtains)
      G.	In case of a power failure, a 12V SLA battery will power the lights.  All lights will turn on.  (Fade set by the remote button’s code sent via IR emitter)
      H.	A-C will have to have some set amount of time to turn off
      I.	D will have to turn off by hitting a panic button again.
      J.	G will turn off once power is restored




