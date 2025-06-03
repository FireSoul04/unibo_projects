/* 1.	Visualizzare i clienti (customers) in ordine alfabetico*/
SELECT *
FROM customers
ORDER BY CompanyName;

/* 2.	Visualizzare i clienti che non hanno il fax*/
SELECT *
FROM customers
WHERE Fax IS NULL;

/* 3.	Selezionare i nomi dei clienti (CompanyName) che iniziano con le lettere P, Q, R, S*/
SELECT CompanyName
FROM customers
WHERE CompanyName LIKE "P%"
OR CompanyName LIKE "Q%"
OR CompanyName LIKE "R%"
OR CompanyName LIKE "S%";

/* 4.	Visualizzare Nome e Cognome degli impiegati assunti (HireDate) dopo il '1993-05-03' e aventi titolo di “Sales Representative”*/
SELECT FirstName, LastName, Title, HireDate
FROM Employees
WHERE HireDate > '1993-05-03'
AND Title = "Sales Representative";

/* 5.	Selezionare la lista dei prodotti non sospesi (attributo discontinued), visualizzando 
anche il nome della categoria di appartenenza*/
SELECT ProductName, CategoryName
FROM Products p, Categories c
WHERE p.CategoryID = c.CategoryID
AND Discontinued IS TRUE;

/* 6. Selezionare gli ordini relativi al cliente ‘Ernst Handel’ (CompanyName)*/
SELECT o.*
FROM Orders o, Customers c
WHERE o.CustomerID = c.CustomerID
AND CompanyName = "Ernst Handel"; 

/* 7.	Selezionare il nome della società e il telefono dei corrieri (shippers) che hanno consegnato 
ordini nella città di ‘Rio de Janeiro’ (ShipCity in orders)
N.B. nella tabella orders l'id corriere è l'attributo ShipVia*/
SELECT DISTINCT o.*
FROM Orders o, Shippers s
WHERE o.ShipVia = s.ShipperID
AND ShipCity = "Rio de Janeiro";

/* 8.	Selezionare gli ordini (OrderID, OrderDate, ShippedDate) per cui la spedizione (ShippedDate)
è avvenuta entro 30 giorni dalla data dell’ordine (OrderDate)*/
SELECT OrderID, OrderDate, ShippedDate
FROM Orders o
WHERE datediff(OrderDate, ShippedDate) < 30;

/* 9.	Selezionare l’elenco dei prodotti che hanno un costo compreso tra 18 e 50, ordinando il risultato
in ordine di prezzo crescente */
SELECT ProductName, UnitPrice
FROM Products
WHERE UnitPrice BETWEEN 18 AND 50
ORDER BY UnitPrice;

/* 10.	Selezionare tutti i clienti (CustomerID, CompanyName) che hanno ordinato il prodotto 'Chang'*/
SELECT DISTINCT c.CustomerID, CompanyName
FROM Products p, `order details` od, Orders o, Customers c
WHERE c.CustomerID = o.CustomerID 
AND o.OrderID = od.OrderID
AND od.ProductID = p.ProductID
AND ProductName = "Chang";

/* 11.	Selezionare i clienti che non hanno mai ordinato prodotti di categoria ‘Beverages’*/
SELECT c.CustomerID
FROM Customers c
WHERE c.CustomerID NOT IN (
	SELECT c.CustomerID
	FROM Products p, `order details` od, Orders o, Categories ct
	WHERE o.OrderID = od.OrderID
	AND od.ProductID = p.ProductID
	AND ct.CategoryID = p.CategoryID
    AND ct.CategoryName = "Beverages"
)
ORDER BY c.CustomerID;
    
/* 12.	Selezionare il prodotto più costoso*/
SELECT ProductID, ProductName, UnitPrice
FROM products
ORDER BY UnitPrice DESC
LIMIT 1;

/* 13.	Visualizzare l’importo totale di ciascun ordine fatto dal cliente 'Ernst Handel' (CompanyName)*/
SELECT SUM(od.Quantity * od.UnitPrice)
FROM `order details` od, orders o, customers c
WHERE o.CustomerID = c.CustomerID
AND o.OrderID = od.OrderID
AND c.CompanyName = "Ernst Handel";

/* 14.	Selezionare il numero di ordini ricevuti in ciascun anno */
SELECT COUNT(*)
FROM orders
GROUP BY YEAR(ShippedDate);

/* 15.	Visualizzare per ogni impiegato (EmployeeID, LastName, FirstName) il numero di clienti distinti serviti per ciascun paese (Country),
visualizzando il risultato in ordine di impiegato e di paese */
SELECT e.EmployeeID, e.LastName, e.FirstName, c.Country, COUNT(DISTINCT c.CustomerID) as CustomersServed
FROM employees e, customers c, orders o
WHERE e.EmployeeID = o.EmployeeID
AND c.CustomerID = o.CustomerID
GROUP BY e.EmployeeID, e.LastName, e.FirstName, c.Country
ORDER BY e.LastName, e.FirstName, c.Country;

/* 16.	Visualizzare per ogni corriere il numero di consegne effettuate, compresi i dati dei 
corrieri che non hanno effettuato nessuna consegna */
SELECT s.ShipperID, s.CompanyName, COUNT(o.OrderID) as ShippedOrders
FROM shippers s LEFT JOIN orders o on (s.ShipperID = o.ShipVia)
GROUP BY s.ShipperID, s.CompanyName;

/* 17.	Visualizzare i fornitori (SupplierID, CompanyName) che forniscono un solo prodotto */
SELECT s.SupplierID, s.CompanyName, p.ProductID
FROM suppliers s, products p
WHERE s.SupplierID = p.SupplierID
GROUP BY s.SupplierID
HAVING COUNT(p.ProductID) = 1;

/* 18.	Visualizzare tutti gli impiegati che sono stati assunti dopo Margaret Peacock */
SELECT DISTINCT e1.EmployeeID, e1.LastName, e1.FirstName, e1.HireDate
FROM employees e1, employees e2
WHERE e2.FirstName = "Margaret"
AND e2.LastName = "Peacock"
AND e1.HireDate >= e2.HireDate;

/* 19.	Visualizzare gli ordini relativi al prodotto più costoso */
SELECT o.*
FROM products p, orders o, `order details` od
WHERE p.ProductID = od.ProductID
AND od.OrderID = o.OrderID
AND p.UnitPrice = (
	SELECT UnitPrice
	FROM products
	ORDER BY UnitPrice DESC
	LIMIT 1
);

/* 20.	Visualizzare i nomi dei clienti per i quali l’ultimo ordine è relativo al 1998  */
SELECT DISTINCT c.CompanyName
FROM customers c, orders o
WHERE o.CustomerID = c.CustomerID
GROUP BY c.CustomerID, c.CompanyName
HAVING MAX(YEAR(o.OrderDate)) = 1998;

/* 21.	Contare il numero di clienti che non hanno effettuato ordini */
SELECT COUNT(c.CustomerID)
FROM customers c
WHERE NOT EXISTS (
	SELECT 1
    FROM orders o
    WHERE o.CustomerID = c.CustomerID
);

/* 22.	Visualizzare il prezzo minimo, massimo e medio dei prodotti per ciascuna categoria */
SELECT c.CategoryID, c.CategoryName, MAX(p.UnitPrice), MIN(p.UnitPrice), AVG(p.UnitPrice)
FROM products p, categories c
WHERE p.CategoryID = c.CategoryID
GROUP BY c.CategoryID;

/* 23.	Selezionare i prodotti che hanno un prezzo superiore al prezzo medio dei prodotti forniti dallo stesso fornitore */
SELECT p1.ProductID, p1.ProductName, p1.UnitPrice
FROM products p1
WHERE p1.UnitPrice >= (
	SELECT AVG(p2.UnitPrice)
    FROM products p2
    WHERE p1.SupplierID = p2.SupplierID
);
                    
/* 24.	Visualizzare, in ordine decrescente rispetto alla quantità totale venduta, i prodotti che hanno venduto una quantità 
totale superiore al prodotto ‘Chai’ */
SELECT p1.ProductID, p1.ProductName, SUM(od.Quantity) SoldProducts
FROM products p1, `order details` od
WHERE p1.ProductID = od.ProductID
GROUP BY p1.ProductID
HAVING SUM(p1.Quantity) >= (
	SELECT SUM(p2.Quantity)
    FROM products p2
    WHERE p2.ProductName = 'Chai'
)
ORDER BY SoldProducts DESC;

/* 25.	Visualizzare il nome dei clienti che hanno fatto almeno due ordini di importo superiore a 15000 */
SELECT c.CompanyName
FROM customers c
GROUP BY c.CustomerID
HAVING 2 <= (
	SELECT COUNT(*)
	FROM `order details` od
	GROUP BY c.CustomerID
	HAVING SUM(od.Quantity * od.UnitPrice) > 15000
);

/* 26.	Individuare i codici dei clienti che hanno fatto un numero di ordini pari a quello del cliente 'Eastern Connection' */
SELECT c.CustomerID
FROM customers c, orders o
WHERE c.CustomerID = o.CustomerID
AND c.CompanyName != 'Eastern Connection'
GROUP BY c.CustomerID
HAVING COUNT(*) = (
	SELECT COUNT(*)
    FROM customers c1, orders o1
    WHERE c1.CustomerID = o1.CustomerID
    AND c1.CompanyName = 'Eastern Connection'
);

/* 27. Visualizzare il numero di ordini ricevuti nel 1997 e di importo superiore a 10000*/
SELECT COUNT(*) orders_received
FROM orders o
WHERE OrderID IN (
	SELECT o1.OrderID
	FROM orders o1, `order details` od, customers c
	WHERE o1.CustomerID = c.CustomerID
	AND o1.OrderID = od.OrderID
	AND YEAR(o1.ShippedDate) > 1997
    GROUP BY o1.OrderID
	HAVING SUM(od.Quantity * od.UnitPrice) > 10000
);

/* 28. Visualizzare i corrieri che hanno consegnato un numero di ordini superiore al numero di ordini consegnati da Speedy Express. */
SELECT s.CompanyName, COUNT(o.OrderID) orders_shipped
FROM shippers s LEFT JOIN orders o ON (o.ShipVia = s.ShipperID)
GROUP BY s.ShipperID
HAVING COUNT(o.OrderID) > (
	SELECT COUNT(o1.OrderID)
    FROM shippers s1 LEFT JOIN orders o1 ON (o1.ShipVia = s1.ShipperID)
    AND s1.CompanyName = 'Speedy Express'
);

/* 29. Visualizzare i clienti che hanno ordinato prodotti di tutte le categorie */
SELECT c.CompanyName, COUNT(p.ProductID) product_per_category
FROM customers c, orders o, `order details` od, products p
WHERE o.CustomerID = c.CustomerID
AND o.OrderID = od.OrderID
AND od.ProductID = p.ProductID
GROUP BY c.CustomerID
HAVING COUNT(DISTINCT p.CategoryID) = (
	SELECT COUNT(*)
    FROM categories c
);