import './App.css';
import ModelViewer from 'react-model-viewer';

const modelPath = 'https://raw.githubusercontent.com/Setsun/static-3d-assets/master/gtlf/sonic/scene.gltf';

function App() {
  return (
    <ModelViewer type="gtlf" src={modelPath} />
  );
}

export default App;
