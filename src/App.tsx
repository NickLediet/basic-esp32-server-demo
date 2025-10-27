import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'
import { useQuery } from '@tanstack/react-query'
const esp32ServerUrl = import.meta.env.VITE_ESP32_SERVER_URL
function App() {
  const { isPending, error, refetch } = useQuery({
    queryKey: ['led-button'],
    queryFn: () => fetch(`http://${esp32ServerUrl}`)
  })


  const [isOn, setIsOn] = useState(false)
  const handleClick = () => {
    setIsOn(!isOn)
    refetch()
  }
  return (
    <>
    {isPending && <div>Loading...</div>}
    {error && <div>Error: {error.message}</div>}
    <div className="button-container">
      <button className={`button ${isOn ? 'on' : 'off'}`} onClick={handleClick}>
        <span className="button-text">{isOn ? 'On' : 'Off'}</span>
      </button>
    </div>
    </>
  )
}

export default App
