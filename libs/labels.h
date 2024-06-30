#ifndef LABELS_H
#define LABELS_H

// Enumeration for payment types
typedef enum Ptype {house, food, entertainment, culture, others};

// Enumeration for house payment subtypes
typedef enum HousePSubtype {rent, gas, electricity, water, internet, others};

// Enumeration for food payment subtypes
typedef enum FoodPSubtype {house, restaurant, takeAway, bar};

// Enumeration for entertainment payment subtypes
typedef enum EntertainmentPSubtype {theater, cinema, holidays};

// Enumeration for culture payment subtypes
typedef enum CulturePSubtype {book, videogame};

// Enumeration for other payment subtypes
typedef enum OtherPSubtype {debt, gift, other};

// Enumeration for income types
typedef enum Itype {work, pension, others};

// Enumeration for work income subtypes
typedef enum WorkISubtype {amphos};

// Enumeration for pension income subtypes
typedef enum PensionISubtype {momDebt, state};

// Enumeration for other income subtypes
typedef enum OtherISubtype {debt, gift, other};

#endif // LABELS_H