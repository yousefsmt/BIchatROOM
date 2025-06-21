# ✈️ Airport Travel Agency Platform

A C++ project simulating a flight reservation platform, developed as the final assignment for the *Advanced Programming* course. The system supports both admin and customer functionalities, including flight management, ticket booking, refunds, and more.

## 📚 Project Overview

This console-based system models a travel agency with two main user roles:

- **Admin**: Manages all flights (domestic and international), with features to add, remove, and view flights.
- **Customer**: Can view available flights, top up their balance, purchase tickets, request refunds, and view their purchase history.

The program follows a class-based OOP design, with extensibility and clean code as core goals.

---

## 🧱 Class Structure

| Class Name        | Description |
|-------------------|-------------|
| `Date`            | Manages date and time of flights |
| `Food`            | Represents in-flight meals (only two types: Economic and Business) |
| `Airport`         | The core platform connecting all flights and logic (base class) |
| `DomesticFlights` | Subclass for domestic flight records |
| `ForeignFlights`  | Subclass for international flight records |
| `DomesticCities`  | Contains internal city names |
| `ForeignCities`   | Contains foreign city names |
| `Customer`        | Manages customer data and interactions |
| `Admin`           | Admin interface and functionalities |
| `Tax`             | Applies a fixed percentage-based tax to ticket prices |

---

## 💡 Features

### Admin Panel
- Add new flights (up to 10 max)
- Delete existing flights
- View all domestic and international flights and their details

### Customer Panel
- View all upcoming flights (sorted by time)
- Add balance to user account
- Purchase flight tickets (with tax calculation)
- Refund purchased tickets (with auto deduction for penalty)
- View purchase history

---

## 📝 Optional Enhancements (for extra credit)

The following features are considered bonus points and are planned for implementation:

- [x] Interactive console menu
- [ ] Colorful UI and basic graphics using ANSI codes
- [ ] File output support for saving ticket and flight info
- [ ] Clean code with appropriate commenting
- [ ] GitHub version control and commits

---

## 🗂️ Example Input/Output Fields

### Customer
- `CustomerID`, `Name`, `Balance`, `PurchasedFlights`, `RefundFlightID`

### Admin
- `AdminID`, `AdminName`, `AdminPassword`, `FlightID`, `FlightType`, `OriginCity`, `DestinationCity`, `Date`, `PlaneName`, `IsCancelled`

### Flight
- Type: `Domestic` / `Foreign`
- Cities: `DomesticCities`, `ForeignCities`
- Food: `Economic`, `Business`

---

## ⚙️ How to Build

Ensure you have a C++ compiler installed (e.g., g++, clang).

```bash
mkdir build
cd build
cmake ../
make
./MyCppProject