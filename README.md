# Physical Computing Project 2024 - IT KMITL
### Project's Title : Vansenger Counter
ระบบนับจำนวนคนเข้า-ออกในรถตู้ด้วย Ultra Sonic Sensor พร้อมแสดงผลที่นั่งว่างผ่าน 7-segment และหน้าเว็บ

## Objective วัตถุประสงค์ของโครงงาน
โครงงานนี้มีจุดประสงค์เพื่อพัฒนาระบบนับจำนวนผู้โดยสารโดยใช้ Arduino WiFi 4 ซึ่งเป็น Microcontroller ที่สามารถประมวลผลและเชื่อมต่ออินเทอร์เน็ตได้ ระบบนี้ใช้เซ็นเซอร์ Ultrasonic สำหรับวัดระยะทางเพื่อตรวจจับการขึ้นและลงของผู้โดยสาร โดยข้อมูลเหล่านี้สามารถตรวจสอบได้ผ่านทางเว็บไซต์ รวมถึงสามารถดูต้นทาง ปลายทางของรถตู้คันนั้น ๆ ได้ด้วย ระบบนี้จะช่วยลดปัญหาการสื่อสารที่ไม่ชัดเจนระหว่างผู้โดยสารกับคนขับ และช่วยเสริมประสิทธิภาพในการจัดการผู้โดยสาร

## Project Description คำอธิบายโครงงาน
โปรเจคนี้เป็นระบบที่ออกแบบมาเพื่อช่วยนับจำนวนคนที่เข้าและออกจากรถตู้ เพื่อแสดงจำนวนที่นั่งว่างแบบเรียลไทม์ โดยใช้เซ็นเซอร์ Ultra Sonic สองตัวในการตรวจจับทิศทางการเคลื่อนที่ของผู้โดยสาร ทั้งนี้ Arduino จะทำหน้าที่ประมวลผลข้อมูลจากเซ็นเซอร์เพื่อคำนวณจำนวนที่นั่งว่างตามเงื่อนไขที่กำหนด:

 1. การทำงานของระบบเซ็นเซอร์:
 * หากเซ็นเซอร์ฝั่งซ้ายตรวจจับก่อนเซ็นเซอร์ฝั่งขวา หมายความว่ามีคนเข้าไปในรถตู้ จำนวนที่นั่งว่างจะลดลง
 * หากเซ็นเซอร์ฝั่งขวาตรวจจับก่อนเซ็นเซอร์ฝั่งซ้าย หมายความว่ามีคนออกจากรถตู้ จำนวนที่นั่งว่างจะเพิ่มขึ้น
 2. การแสดงผลข้อมูล:
 * จำนวนที่นั่งว่างจะแสดงผลผ่าน 7-segment บนตัวเครื่อง Arduino เพื่อให้เห็นสถานะปัจจุบันได้ทันที
 * ข้อมูลเดียวกันนี้จะถูกส่งไปแสดงผลบนหน้าเว็บ เพื่อให้สามารถตรวจสอบได้จากระยะไกลผ่านอุปกรณ์ที่เชื่อมต่ออินเทอร์เน็ต

## Website
https://mallowdoodee.github.io/PhysicalComputingProject2024/web/index

## Video Presentation
[Vansenger Counter Presentation](https://youtu.be/k6WqcArX3Ns?si=X9XE2-Kmy4_-SsKC)

## Poster A1
[A1 Poster PDF](A1%20Poster.pdf)

## TEAM MEMBER
* 66070127 พรทิพย์ สอนสุจิตรา
* 66070132 พิชชากานต์ เกริกกวิน
* 66070175 รัตนาภรณ์ มธุรัสสกุล
* 66070287 ปภาวดี จันทร์สอน

|Student ID|Name|Topic|Profile|
|--|--|--|--|
| 66070127 | นางสาวพรทิพย์ สอนสุจิตรา | Website | <img alt="66070127" height="200" src="assets/66070127.JPG" width="200"/> |
| 66070132 | นางสาวพิชชากานต์ เกริกกวิน | Arduino Circuit Designer & .ino |<img alt="66070132" height="200" src="assets/66070132.jpg" width="150"/>|
| 66070175 | นางสาวรัตนาภรณ์ มธุรัสสกุล | Poster & Website |<img alt="66070175" height="200" src="assets/66070175.jpg" width="150"/>|
| 66070287 | นางสาวปภาวดี จันทร์สอน | Arduino Circuit Designer & .ino |<img alt="66070287" height="200" src="assets/66070287.jpg" width="150"/>|

## นำเสนอ
* รองศาสตราจารย์ ดร. กิติ์สุชาต พสุภา
* รองศาสตราจารย์ ดร. ปานวิทย์ ธุวะนุติ
