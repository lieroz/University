USE Travels

CREATE TABLE users (
  id         INT IDENTITY (1, 1),
  email      NVARCHAR(100) NOT NULL,
  first_name NVARCHAR(100) NOT NULL,
  last_name  NVARCHAR(100) NOT NULL,
  birth_date DATETIME      NOT NULL
);

CREATE TABLE locations (
  id       INT IDENTITY (1, 1),
  country  NVARCHAR(100) NOT NULL,
  place    NVARCHAR(100) NOT NULL,
  currency NVARCHAR(100) NOT NULL
);

CREATE TABLE visits (
  id         INT IDENTITY (1, 1),
  visited_at DATETIME NOT NULL,
  days_spent INT      NOT NULL
);

CREATE TABLE ulv (
  u_id INT,
  l_id INT,
  v_id INT,
  mark INT
);