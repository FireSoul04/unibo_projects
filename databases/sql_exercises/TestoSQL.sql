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
SELECT o.*
FROM Orders o, Shippers s
WHERE o.ShipVia = s.ShipperID
AND ShipCity = "Rio de Janeiro";

/* 8.	Selezionare gli ordini (OrderID, OrderDate, ShippedDate) per cui la spedizione (ShippedDate)
è avvenuta entro 30 giorni dalla data dell’ordine (OrderDate)*/
SELECT OrderID, OrderDate, ShippedDate
FROM Orders o
WHERE datediff(OrderDate, ShippedDate) <= 30;

/* 9.	Selezionare l’elenco dei prodotti che hanno un costo compreso tra 18 e 50, ordinando il risultato
in ordine di prezzo crescente */
SELECT ProductName, UnitPrice
FROM Products
WHERE UnitPrice BETWEEN 18 AND 50
ORDER BY UnitPrice;

/* 10.	Selezionare tutti i clienti (CustomerID, CompanyName) che hanno ordinato il prodotto 'Chang'*/
SELECT c.CustomerID, CompanyName
FROM Products p, `order details` od, Orders o, Customers c
WHERE c.CustomerID = o.CustomerID 
AND o.OrderID = od.OrderID
AND od.ProductID = p.ProductID
AND ProductName = "Chang";

/* 11.	Selezionare i clienti che non hanno mai ordinato prodotti di categoria ‘Beverages’*/
SELECT DISTINCT c.CustomerID
FROM Products p, `order details` od, Orders o, Customers c, Categories ct
WHERE c.CustomerID = o.CustomerID 
AND o.OrderID = od.OrderID
AND od.ProductID = p.ProductID
AND ct.CategoryID = p.CategoryID
NOT IN (
	SELECT DISTINCT c.CustomerID
	FROM Products p, `order details` od, Orders o, Customers c, Categories ct
	WHERE c.CustomerID = o.CustomerID 
	AND o.OrderID = od.OrderID
	AND od.ProductID = p.ProductID
	AND ct.CategoryID = p.CategoryID
    AND ct.CategoryName = "Beverages"
)
ORDER BY c.CustomerID;
    
/* 12.	Selezionare il prodotto più costoso*/

/* 13.	Visualizzare l’importo totale di ciascun ordine fatto dal cliente 'Ernst Handel' (CompanyName)*/

/* 14.	Selezionare il numero di ordini ricevuti in ciascun anno */

/* 15.	Visualizzare per ogni impiegato (EmployeeID, LastName, FirstName) il numero di clienti distinti serviti per ciascun paese (Country),
visualizzando il risultato in ordine di impiegato e di paese*/

/* 16.	Visualizzare per ogni corriere il numero di consegne effettuate, compresi i dati dei 
corrieri che non hanno effettuato nessuna consegna */

/* 17.	Visualizzare i fornitori (SupplierID, CompanyName) che forniscono un solo prodotto */

/* 18.	Visualizzare tutti gli impiegati che sono stati assunti dopo Margaret Peacock */

/* 19.	Visualizzare gli ordini relativi al prodotto più costoso */
                                       
/* 20.	Visualizzare i nomi dei clienti per i quali l’ultimo ordine è relativo al 1998  */

/* 21.	Contare il numero di clienti che non hanno effettuato ordini */
                         
/* 22.	Visualizzare il prezzo minimo, massimo e medio dei prodotti per ciascuna categoria */

/* 23.	Selezionare i prodotti che hanno un prezzo superiore al prezzo medio dei prodotti forniti dallo stesso fornitore */
                    
/* 24.	Visualizzare, in ordine decrescente rispetto alla quantità totale venduta, i prodotti che hanno venduto una quantità 
totale superiore al prodotto ‘Chai’ */

/* 25.	Visualizzare il nome dei clienti che hanno fatto almeno due ordini di importo superiore a 15000 */

/* 26.	Individuare i codici dei clienti che hanno fatto un numero di ordini pari a quello del cliente 'Eastern Connection' */

/* 27. Visualizzare il numero di ordini ricevuti nel 1997 e di importo superiore a 10000*/

/* 28. Visualizzare i corrieri che hanno consegnato un numero di ordini superiore al numero di ordini consegnati da Speedy Express. */

/* 29. Visualizzare i clienti che hanno ordinato prodotti di tutte le categorie */

                     

