----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:34:16 05/13/2021 
-- Design Name: 
-- Module Name:    Principal - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Principal is
    Port ( Dividendo : in  STD_LOGIC_VECTOR (6 downto 0);
           Divisor : in  STD_LOGIC_VECTOR (3 downto 0);
           Cociente : out  STD_LOGIC_VECTOR (3 downto 0));
end Principal;

architecture Behavioral of Principal is

function suma_resta(A, B, Cin, M : STD_LOGIC) return STD_LOGIC is
begin
	return ((A XOR B) XOR (M XOR Cin));
end suma_resta;

function acarreo(A, B, Cin, M : STD_LOGIC) return STD_LOGIC is
begin
	return ((A AND Cin) OR ((M XOR B) AND (A OR Cin)));
end acarreo;

type matriz is array (0 to 3, 0 to 3) of STD_LOGIC;

signal a, c: matriz;
signal M : STD_LOGIC;

begin
M<='1';
fori: for i in 0 to 3 generate
	iffilasprimero: if i = 3 generate
		forj: for j in 0 to 3 generate
			ifcolumnasprimeroprimero: if j = 0 generate
				a(i,j)<=suma_resta(Dividendo(i+j), Divisor(j), M, M);
				c(i,j)<=acarreo(Dividendo(i+j), Divisor(j), M, M);
			end generate;
			ifcolumnasprimerosegundo: if j > 0 generate
				a(i, j)<=suma_resta(Dividendo(i+j), Divisor(j), c(i,j-1), M);
				c(i, j)<=acarreo(Dividendo(i+j), Divisor(j), c(i,j-1), M);
			end generate;
		end generate;	
	end generate;
	
	iffilassegundo: if i < 3 generate
		forj: for j in 0 to 3 generate
			ifcolumnassegundoprimero: if j = 0 generate
				a(i, j)<=suma_resta(Dividendo(i), Divisor(j), c(i+1,3), c(i+1,3));
				c(i, j)<=acarreo(Dividendo(i), Divisor(j), c(i+1,3), c(i+1,3));
			end generate;
			ifcolumnassegundosegundo: if j > 0 generate
				a(i, j)<=suma_resta(a(i+1,j-1), Divisor(j), c(i,j-1), c(i+1,3));
				c(i, j)<=acarreo(a(i+1,j-1), Divisor(j), c(i,j-1), c(i+1,3));
			end generate;
		end generate;	
	end generate;
	Cociente(i)<=c(i,3);
end generate;

--Cociente<="1111";

end Behavioral;

