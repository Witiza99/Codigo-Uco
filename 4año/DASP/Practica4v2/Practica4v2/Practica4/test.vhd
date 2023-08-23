--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   20:08:51 05/14/2021
-- Design Name:   
-- Module Name:   E:/xinlinx/Practica4/test.vhd
-- Project Name:  Practica4
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: Principal
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY test IS
END test;
 
ARCHITECTURE behavior OF test IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Principal
    PORT(
         Dividendo : IN  std_logic_vector(6 downto 0);
         Divisor : IN  std_logic_vector(3 downto 0);
         Cociente : OUT  std_logic_vector(3 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal Dividendo : std_logic_vector(6 downto 0) := (others => '0');
   signal Divisor : std_logic_vector(3 downto 0) := (others => '0');

 	--Outputs
   signal Cociente : std_logic_vector(3 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Principal PORT MAP (
          Dividendo => Dividendo,
          Divisor => Divisor,
          Cociente => Cociente
        );

   -- Stimulus process
   stim_proc: process
   begin		
      Dividendo<="0000110";
		Divisor<="0011";
      wait for 200 ns;	
		
		Dividendo<="0001110";
		Divisor<="0010";
      wait for 200 ns;	
		
		Dividendo<="0010000";
		Divisor<="0100";
      wait for 200 ns;	
		
		Dividendo<="0010100";
		
      wait for 200 ns;	
		Dividendo<="0010101";
		Divisor<="0110";
      wait for 200 ns;	
		
		Dividendo<="0010001";
		Divisor<="0011";
      wait for 200 ns;
		wait;
   end process;

END;
